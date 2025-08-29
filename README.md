# Console Editor
Project contains compact console reader and editor of the **XML** files, e.g. files with the recipe structure

# Set Up
- Linux-based OS
- C++ 17
- CMake ```3.28.3``` (version with ```FetchContent``` support)
- perl `v5.36.0` and higher
- Create building **config**, download necessary **libraries** and generate **Makefile** (run from the `/build` dir):
	```bash
	cmake ..
	```

# Build & Run
- Build the project (execute from the `/build` dir):
	```bash
	make
	```
- Run (execute from the `/build` dir):
	```bash
	./console-editor
	```
- Rebuild libs and source code (execute from the `/build` dir):
	```bash
	make
	```

# Dependencies
- Libraries: 
    |   Name   |    Type   |                            Link                                  |
    |----------|-----------|------------------------------------------------------------------|
    |  `ftxui` |  license  | [MIT](https://github.com/ArthurSonzogni/FTXUI/blob/main/LICENSE) |
    |  `pugi`  |  license  | [MIT](https://github.com/zeux/pugixml/blob/master/LICENSE.md)    |  