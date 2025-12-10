PHONY: setup 

setup:
	conan install . --build=missing -s build_type=Debug -of=build/Debug
	conan install . --build=missing -s build_type=Release -of=build/Release
