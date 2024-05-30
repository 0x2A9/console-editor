#include "utils/fs.hpp"
#include "managers/fs_manager.hpp"

#include <filesystem>
#include <string>
#include <vector>

std::shared_ptr<std::vector<std::string>> FsManager::GetTopLvDirsNames(const std::string &path) {
  if (this->top_lv_dirs_names_ == nullptr) {
    auto n = GetResourcesNames(GetFullPathsToContent(path).dirs);
    this->top_lv_dirs_names_ = std::make_shared<std::vector<std::string>>(n);
  }
  return this->top_lv_dirs_names_;
}

std::shared_ptr<std::vector<std::string>> FsManager::GetFirstLvContentNames(const std::string &path) {
  if (this->first_lv_content_names_ == nullptr) {
    auto n = GetResourcesNames(GetFullPathsToContent(path).all);
    this->first_lv_content_names_ = std::make_shared<std::vector<std::string>>(n);
  }
  return this->first_lv_content_names_;
}

std::string FsManager::GetTopLvSelectedDirFullPath(const int &sel) {
  return static_cast<std::string>(kRootDir) +
         static_cast<std::string>(kDataDir) + '/' +
         (*this->top_lv_dirs_names_)[sel];
}

std::string FsManager::GetFirstLvSelectedDirFullPath(const std::string &out_dirs, const int &sel) {
  return out_dirs + '/' +
         (*this->first_lv_content_names_)[sel];
}
