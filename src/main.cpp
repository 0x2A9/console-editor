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
 
ftxui::ButtonOption ButtonStyle() {
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

ftxui::InputOption InputStyle() {
   return ftxui::InputOption::Spacious();
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

  // auto proc = RecipesProc(full_path);
  // auto all_text = proc->StringFromXml();

  auto all_text = GetFileContent(full_path);

  /* formating and rendering */
  auto btn_save = ftxui::Button("Save", [&screen, full_path, &all_text] { 
    screen.Exit(); WriteContentToFile(full_path, all_text); 
  }, ButtonStyle());

  auto btn_back = ftxui::Button("Back", [&screen, top_lv_menu] { 
    screen.Loop(top_lv_menu); 
  }, ButtonStyle());

  int row = 0;

  auto content = ftxui::Input(&all_text, InputStyle());
  auto form = ftxui::Container::Vertical({
    ftxui::Container::Horizontal({btn_save, btn_back}, &row) | ftxui::flex,
    ftxui::Container::Horizontal({content}, &row) | 
    ftxui::flex | 
    ftxui::vscroll_indicator | 
    ftxui::frame | 
    ftxui::size(ftxui::HEIGHT, ftxui::LESS_THAN, 25),
  });

  auto component = ftxui::Renderer(form, [&] {
    return ftxui::vbox({
      ftxui::text("Choose the action:"),
      ftxui::separator(),
      form->Render() | ftxui::flex,
    }) |
    ftxui::flex | ftxui::border;
  });
  
  screen.Loop(component);
}
