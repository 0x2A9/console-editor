#include <string>

#include "ftxui/component/component.hpp"
#include "ftxui/component/component_options.hpp"   
#include "ftxui/component/screen_interactive.hpp"
#include "pugixml.hpp"

#include "utils/fs.hpp" 
#include "xml_processors/processor.hpp"
#include "utils/ui.hpp"

// executable is placed inside the `build` dir
const char *ROOT_DIR = "./..";
// the path is relative to the project root
const char *DATA_DIR = "/data";

int main() {
  /* common */
  auto screen = ftxui::ScreenInteractive::TerminalOutput();
  int selected = 0;

  ftxui::MenuOption option;
  option.on_enter = screen.ExitLoopClosure();

  /* top level dir */
  auto data_full_path = static_cast<std::string>(ROOT_DIR) + 
                        static_cast<std::string>(DATA_DIR);
  auto top_lv_dirs_names = GetResourcesNames(GetFullPathsToContent(data_full_path).dirs);

  auto top_lv_menu = Menu(&top_lv_dirs_names, &selected, option);
  screen.Loop(top_lv_menu);

  auto top_lv_selected_dir_full_path = 
      static_cast<std::string>(DATA_DIR) + "/" + top_lv_dirs_names[selected];
  
  /* first level dir */
  auto first_lv_content_names = 
      GetResourcesNames(GetFullPathsToContent(ROOT_DIR + top_lv_selected_dir_full_path).all);

  selected = 0;

  auto selected_dir_menu = Menu(&first_lv_content_names, &selected, option);
  screen.Loop(selected_dir_menu);

  auto first_lv_selected_dir_full_path = 
      top_lv_selected_dir_full_path + "/" + first_lv_content_names[selected];

  /* xml file interaction */
  auto full_path = ROOT_DIR + first_lv_selected_dir_full_path;
  auto raw_content = GetFileContent(full_path);

  /* formating and rendering */
  auto btn_exit = CreateExitButton("Exit", screen);

  auto btn_edit = ftxui::Button("Edit", [&screen, full_path, &raw_content] { 
    auto btn_save = ftxui::Button("Save", [&screen, full_path, &raw_content] { 
      screen.Exit(); 
      WriteContentToFile(full_path, raw_content); 
    }, ButtonStyle());

    auto btn_back = CreateExitButton("Back", screen);
    CreateForm(&raw_content, {btn_save, btn_back}, screen);
  }, ButtonStyle());

  auto content = RecipesProc(full_path)->StringFromXml();

  CreateForm(&content, {btn_edit, btn_exit}, screen);
}
