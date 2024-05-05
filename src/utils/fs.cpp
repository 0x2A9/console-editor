#include <filesystem>
#include <iostream>
#include <string>
#include <sys/stat.h>
#include <vector>
#include <unordered_map>
#include <fstream>

#include "utils/fs.hpp"

namespace fs = std::filesystem;

static bool IsDir(const char* path) {
  // this structure would distinguish a file from adirectory
  struct stat sb;

  // checking whether the path points to a directory or not
  return stat(path, &sb) == 0 && (sb.st_mode & S_IFDIR);
}

void RenameDirs(std::string path, std::string postfix) {
  auto full_paths = GetFullPathsToContent(path).dirs;

  for (auto dir: full_paths) {
    auto n = SplitName(SplitPath(dir).name).n;

    std::string new_name = *path.c_str() + "/" + n + "_" + postfix;
    rename(dir.c_str(), new_name.c_str());
  }
}

struct Content GetFullPathsToContent(std::string path) {
  struct Content full_paths;

  for (const auto& item : fs::directory_iterator(path)) {
    // converting the path to const char * in the subsequent lines
    fs::path out_file_name = item.path();
    std::string out_file_name_str = out_file_name.string();
    const char* path = out_file_name_str.c_str();

    full_paths.all.push_back(path);

    IsDir(path) ? full_paths.dirs.push_back(path) : full_paths.files.push_back(path);
  }

  return full_paths;
}

std::vector<std::string> GetResourcesNames(std::vector<std::string> full_paths) {
  std::vector<std::string> names;

  for (auto path: full_paths) {
    names.push_back(SplitPath(path).name);
  }
  
  return names;
}

std::string GetFileContent(std::string path) {
  std::string line;
  std::ifstream f(path);
  std::string all_text;

  while (getline(f, line)) {
    all_text += line + "\n";
  }

  f.close();

  return all_text;
}

struct ResourcePath SplitPath(std::string& str) {
  std::size_t found = str.find_last_of("/\\");
  std::string path = str.substr(0, found);
  std::string name = str.substr(found + 1);

  struct ResourcePath rp = {
    path, 
    name
  };

  return rp;
}

struct ResourceName SplitName(std::string str) {
  std::size_t found = str.find("_");
  std::string n = str.substr(0, found);
  std::string postfix = str.substr(found + 1);

  struct ResourceName rn = {
    postfix,
    n
  };

  return rn;
}
