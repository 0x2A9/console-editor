#include "managers/render_manager.hpp"
#include "managers/fs_manager.hpp"
#include "utils/fs.hpp"
#include "utils/ui.hpp"
#include "xml_processors/processor.hpp"

void RenderManager::Process() {
  const std::string data_path = std::string(kRootDir) + std::string(kDataDir);
  FsManager fsm = FsManager();

  /* first level dir */
  auto top_lv_dirs_names = fsm.GetTopLvDirsNames(data_path);
  auto top_lv_menu = Menu(top_lv_dirs_names.get(),
                          &this->sel_,
                          MenuStyle(this->screen_));
  this->screen_.Loop(top_lv_menu);

  auto top_lv_selected_dir_full_path = fsm.GetTopLvSelectedDirFullPath(this->sel_);

  /* first level dir */
  auto first_lv_content_names =
      fsm.GetFirstLvContentNames(top_lv_selected_dir_full_path);
  auto selected_dir_menu = Menu(first_lv_content_names.get(),
                                &this->sel_,
                                MenuStyle(this->screen_));
  this->screen_.Loop(selected_dir_menu);

  auto full_path = fsm.GetFirstLvSelectedDirFullPath(top_lv_selected_dir_full_path,
                                                     this->sel_);

  /* xml file interaction */
  auto raw_content = GetFileContent(full_path);

  /* formating and rendering */
  auto btn_exit = CreateExitButton("Exit", this->screen_);

  auto btn_edit = ftxui::Button("Edit", [this, full_path, &raw_content] {
    auto btn_save = ftxui::Button("Save", [this, full_path, &raw_content] {
      this->screen_.Exit();
      WriteContentToFile(full_path, raw_content);
    }, ButtonStyle());

    auto btn_back = CreateExitButton("Back", this->screen_);
    CreateForm(&raw_content, {btn_save, btn_back}, this->screen_);
  }, ButtonStyle());

  auto content = RecipesProc(full_path)->StringFromXml();

  CreateForm(&content, {btn_edit, btn_exit}, this->screen_);
}
