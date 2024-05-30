#ifndef CONSOLE_EDITOR_UTILS_FS_HPP
#define CONSOLE_EDITOR_UTILS_FS_HPP

#include <string>
#include <vector>

// executable is placed inside the `build` dir
static const char *kRootDir = "./..";
// the path is relative to the project root
static const char *kDataDir = "/data";

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

void RenameDirs(std::string path, std::string postfix);
struct Content GetFullPathsToContent(const std::string &path);
std::vector<std::string> GetResourcesNames(const std::vector<std::string> &full_paths);
std::string GetFileContent(const std::string &path);
void WriteContentToFile(const std::string &path, const std::string &content);
struct ResourcePath SplitPath(const std::string &str);
struct ResourceName SplitName(const std::string &str);

#endif // CONSOLE_EDITOR_UTILS_FS_HPP
