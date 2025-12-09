#include "crow.h"
#include <crow/http_response.h>
#include <fstream>
#include <ios>

int main() {
  crow::SimpleApp app; // define your crow application

  // define your endpoint at the root directory
  CROW_ROUTE(app, "/")([]() {
    crow::response res;
    std::string fileName = "res/static/test_files/test.jpg";
    std::stringstream imageBuffer;

    // read example image
    std::ifstream imageReq(fileName, std::ios_base::binary);
    if (!imageReq) {
      std::cout << "Error reading the image";
      imageReq.close();
      return crow::response(500, "Error getting image");
    }

    if (imageReq.is_open()) {
      imageBuffer << imageReq.rdbuf();
    }

    std::uintmax_t filesize = std::filesystem::file_size(fileName);
    // do some bound checking.
    std::cout << filesize << std::endl;

    std::string mime = "image/jpg";
    res.set_header("Content-Type", mime);
    res.body = imageBuffer.str();

    return res;
  });

  // set the port, set the app to run on multiple threads, and run the app
  app.port(18080).multithreaded().run();
}
