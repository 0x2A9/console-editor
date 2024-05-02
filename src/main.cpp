#include <string>      
#include <iostream>
#include <functional>
#include <stdlib.h>
 
#include "ftxui/component/captured_mouse.hpp"
#include "ftxui/component/component.hpp"    
#include "ftxui/component/component_base.hpp"       
#include "ftxui/component/component_options.hpp"   
#include "ftxui/component/screen_interactive.hpp"  
#include "ftxui/dom/elements.hpp" 
#include "pugixml.hpp"

#include "utils/fs.hpp" 
#include "xml_processors/processor.hpp"

// executable is placed inside the `build` dir
const char *ROOT_DIR = "./..";
// the path is relative to the project root
const char *DATA_DIR = "/data";
 
ftxui::ButtonOption Style() {
  auto option = ftxui::ButtonOption::Animated();
  option.transform = [](const ftxui::EntryState& s) {
    auto element = ftxui::text(s.label);
    if (s.focused) {
      element |= ftxui::bold;
    }
    return element | ftxui::center | ftxui::borderEmpty | ftxui::flex;
  };
  return option;
}

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

  std::cout << "Selected: >" << top_lv_selected_dir_full_path << std::endl;
  
  /* first level dir */
  auto first_lv_content_names = 
      GetResourcesNames(GetFullPathsToContent(ROOT_DIR + top_lv_selected_dir_full_path).all);

  selected = 0;

  auto selected_dir_menu = Menu(&first_lv_content_names, &selected, option);
  screen.Loop(selected_dir_menu);

  auto first_lvs_selected_dir_full_path = 
      top_lv_selected_dir_full_path + "/" + first_lv_content_names[selected];

  std::cout << "Selected: " << first_lvs_selected_dir_full_path << std::endl;

  /* xml file interaction */
  auto full_path = ROOT_DIR + first_lvs_selected_dir_full_path;
  
  auto proc = RecipesProc(full_path);
  
  std::string all_text = proc->StringFromXml();

  /* formating and rendering */
  auto btn_edit = ftxui::Button("Edit", [&] {}, Style());
  auto btn_back = ftxui::Button("Back", [&] {}, Style());

  int row = 0;
  auto content = ftxui::Input(&all_text);
  auto buttons = ftxui::Container::Vertical({
    ftxui::Container::Horizontal({btn_edit, btn_back}, &row) | ftxui::flex,
    ftxui::Container::Horizontal({content}, &row) | ftxui::flex,
  });

  auto component = ftxui::Renderer(buttons, [&] {
    return ftxui::vbox({
      ftxui::text("Choose the action"),
      ftxui::separator(),
      buttons->Render() | ftxui::flex,
    }) |
    ftxui::flex | ftxui::border;
  });
  
  screen.Loop(component);
}
