#include <filesystem>
#include <string>
#include <sys/stat.h>
#include <vector>
#include <fstream>

#include "utils/fs.hpp"

namespace fs = std::filesystem;

static bool IsDir(const char* path) {
  // this structure would distinguish a file from a directory
  struct stat sb;

  // checking whether the path points to a directory or not
  return stat(path, &sb) == 0 && (sb.st_mode & S_IFDIR);
}

void RenameDirs(std::string &path, const std::string &postfix) {
  auto full_paths = GetFullPathsToContent(path).dirs;

  for (const auto &dir: full_paths) {
    auto n = SplitName(SplitPath(dir).name).n;

    std::string new_name = path.append({'/'}).append(n).append({'_'}).append(postfix);
    rename(dir.c_str(), new_name.c_str());
  }
}

struct Content GetFullPathsToContent(const std::string& path) {
  struct Content full_paths;

  for (const auto& item : fs::directory_iterator(path)) {
    // converting the path to const char * in the subsequent lines
    const fs::path *out_file_name = &item.path();
    std::string out_file_name_str = out_file_name->string();
    const char* full_path = out_file_name_str.c_str();

    full_paths.all.emplace_back(full_path);

    IsDir(full_path) ? full_paths.dirs.emplace_back(full_path) : full_paths.files.emplace_back(full_path);
  }

  return full_paths;
}

std::vector<std::string> GetResourcesNames(const std::vector<std::string> &full_paths) {
  std::vector<std::string> names;

  for (const auto &path : full_paths) {
    names.emplace_back(SplitPath(path).name);
  }
  
  return names;
}

std::string GetFileContent(const std::string &path) {
  std::string line;
  std::ifstream f(path);
  std::string all_text;

  while (getline(f, line)) {
    all_text += line + "\n";
  }

  f.close();

  return all_text;
}

void WriteContentToFile(const std::string &path, const std::string &content) {
  std::ofstream f(path);

  f << content;

  f.close();
}

struct ResourcePath SplitPath(const std::string &str) {
  std::size_t found = str.find_last_of("/\\");
  std::string path = str.substr(0, found);
  std::string name = str.substr(found + 1);

  struct ResourcePath rp = {
    path, 
    name
  };

  return rp;
}

struct ResourceName SplitName(const std::string &str) {
  std::size_t found = str.find('_');
  std::string n = str.substr(0, found);
  std::string postfix = str.substr(found + 1);

  struct ResourceName rn = {
    postfix,
    n
  };

  return rn;
}
