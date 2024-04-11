## Building the project

### Create building config and Makefile, build the project and run it
- execute from the `/build` dir:
```
    cmake ..
    make
    ./console-editor
```

### Rebuild libs and source code
- execute from the `/build` dir:
```
    make
```


## Dependencies
- Platform - Linux
- GCC `v11` and higher
- CMake (version with FetchContent support)
- perl `v5.36.0` and higher
- Libraries: 
    - `ftxui` - license [MIT](https://github.com/ArthurSonzogni/FTXUI/blob/main/LICENSE)