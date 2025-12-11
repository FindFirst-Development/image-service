PHONY: setup lint tidy

setup:
	conan install . --build=missing -s build_type=Debug -of=build/Debug
	conan install . --build=missing -s build_type=Release -of=build/Release

lint: 
	@find . -iname "*.cpp"  -not -path "./build/*" -o -iname "*.h" -not -path "./build/*" | xargs clang-format -i
	@echo "Formatted all c++ and h files to format."

tidy: 
	run-clang-tidy -p build/Release

