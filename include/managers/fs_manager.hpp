#ifndef CONSOLE_EDITOR_MANAGERS_FS_MANAGER_HPP
#define CONSOLE_EDITOR_MANAGERS_FS_MANAGER_HPP

#include "utils/fs.hpp"

#include <memory>
#include <string>
#include <vector>

class FsManager {
 public:
  explicit FsManager() = default;
  std::shared_ptr<std::vector<std::string>> GetTopLvDirsNames(const std::string &path);
  std::shared_ptr<std::vector<std::string>> GetFirstLvContentNames(const std::string &path);
  std::string GetTopLvSelectedDirFullPath(const int &sel);
  std::string GetFirstLvSelectedDirFullPath(const std::string &out_dirs, const int &sel);

 private:
  std::shared_ptr<std::vector<std::string>> top_lv_dirs_names_ = nullptr;
  std::shared_ptr<std::vector<std::string>> first_lv_content_names_ = nullptr;
};

#endif // CONSOLE_EDITOR_MANAGERS_FS_MANAGER_HPP
