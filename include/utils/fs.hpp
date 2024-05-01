#ifndef FS_H
#define FS_H

#include <string>
#include <vector>

// executable is placed inside the `build` dir
const std::string ROOT_DIR = "./..";
// the path is relative to the project root
const std::string DATA_DIR = "/data";

struct ResourcePath {
    std::string location;
    std::string name;
};

struct ResourceName {
    std::string postfix;
    std::string n;
};

struct Content {
    std::vector<std::string> dirs;
    std::vector<std::string> files;
    std::vector<std::string> all;
};

void renameDirs(std::string path, std::string postfix);
struct Content getFullPathsToContent(std::string path);
std::vector<std::string> getResourcesNames(std::vector<std::string> fullPaths);
struct ResourcePath splitPath(std::string& str);
struct ResourceName splitName(std::string str);

#endif // FS_H
