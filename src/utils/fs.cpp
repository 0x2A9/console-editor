#include <filesystem>
#include <iostream>
#include <string>
#include <sys/stat.h>
#include <vector>
#include <unordered_map>

#include "utils/fs.hpp"

namespace fs = std::filesystem;

static bool isDir(const char* path) 
{
    // this structure would distinguish a file from adirectory
    struct stat sb;

    // checking whether the path points to a directory or not
    return stat(path, &sb) == 0 && (sb.st_mode & S_IFDIR);
}

void renameDirs(std::string path, std::string postfix)
{
    auto fullPaths = getFullPathsToContent(path).dirs;

    for (auto dir: fullPaths) {
        auto n = splitName(splitPath(dir).name).n;

        std::string newName = ROOT_DIR + path.c_str() + "/" + n + "_" + postfix;
        rename(dir.c_str(), newName.c_str());
    }
}

struct Content getFullPathsToContent(std::string path) 
{
    path = ROOT_DIR + path;
    struct Content fullPaths;

    for (const auto& item : fs::directory_iterator(path)) {
        // converting the path to const char * in the subsequent lines
        fs::path outfilename = item.path();
        std::string outfilename_str = outfilename.string();
        const char* path = outfilename_str.c_str();

        fullPaths.all.push_back(path);

        isDir(path) ? fullPaths.dirs.push_back(path) : fullPaths.files.push_back(path);
    }

    return fullPaths;
}

std::vector<std::string> getResourcesNames(std::vector<std::string> fullPaths)
{
    std::vector<std::string> names;

    for (auto path: fullPaths) {
        names.push_back(splitPath(path).name);
    }
    
    return names;
}

struct ResourcePath splitPath(std::string& str)
{
    std::size_t found = str.find_last_of("/\\");
    std::string path = str.substr(0, found);
    std::string name = str.substr(found + 1);

    struct ResourcePath rp = {
        path, 
        name
    };

    return rp;
}

struct ResourceName splitName(std::string str) 
{
    std::size_t found = str.find("_");
    std::string n = str.substr(0, found);
    std::string postfix = str.substr(found + 1);

    struct ResourceName rn = {
        postfix,
        n
    };

    return rn;
}
