#ifndef FS_H
#define FS_H

#include <string>
#include <vector>

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

#endif // FS_H
