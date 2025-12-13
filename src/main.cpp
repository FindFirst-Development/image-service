#include "crow.h"
#include <crow/http_response.h>
#include <cstddef>
#include <cstdlib>
#include <fstream>
#include <ios>
#include <string>

int main() {
  crow::SimpleApp app; // define your crow application

  constexpr std::size_t MAX_SIZE =
      150ULL * 1024 * 1024; // 150 MiB max file size.

  // define your endpoint at the root directory
  CROW_ROUTE(app, "/<path>")([](std::filesystem::path image_name) {
    std::string img_dir_path = "res/static/test_files/";
    const char *img_dir = std::getenv("IMAGE_DIR");
    // ensure that the env path exists before switching from safe default.
    if (std::filesystem::exists(img_dir_path)) {
      img_dir_path = std::string(img_dir);
    }

    std::string filename = img_dir_path + image_name.filename().string();
    std::string ext;

    // checks
    if (!std::filesystem::exists(filename)) {
      return crow::response(404, "Image does not exist.");
    }

    if (image_name.has_extension()) {
      ext = image_name.extension().string().erase(0, 1);
      if (ext != "png" && ext != "jpeg" && ext != "jpg") {
        return crow::response(500, "Images only supported");
      }
    } else {
      return crow::response(400, "Images only supported");
    }

    std::uintmax_t filesize = std::filesystem::file_size(filename);
    if (filesize > MAX_SIZE) {
      return crow::response(400, "Error getting image: image too large.");
    }

    // read example image
    std::ifstream img(filename, std::ios_base::binary);
    // output buffer
    std::stringstream out;

    if (!img.is_open()) {
      std::cout << "Error reading the image";
      return crow::response(500, "Error getting image");
    }

    std::string s;
    s.resize(static_cast<size_t>(filesize));
    img.read(&s[0], filesize);

    // close the image file.
    img.close();

    std::string mime = "image/" + ext;
    crow::response res;
    res.set_header("Content-Type", mime);
    res.body = s;

    return res;
  });

  // set the port, set the app to run on multiple threads, and run the app
  app.port(18080).multithreaded().run();
}
