#include <string>    
#include <vector>    
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
 
ftxui::ButtonOption style() {
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

enum ParagraphTag {
    Name = 1,
    Ingredient = 2,
    Direction = 3
};

std::unordered_map<std::string, ParagraphTag> tagMapping = 
{
    { "Name", ParagraphTag::Name },
    { "Ingredient", ParagraphTag::Ingredient },
    { "Direction", ParagraphTag::Direction }
};

int main() 
{
    /* common */
    auto screen = ftxui::ScreenInteractive::TerminalOutput();
    int selected = 0;

    ftxui::MenuOption option;
    option.on_enter = screen.ExitLoopClosure();

    /* top level dir */
    auto topLvDirsNames = 
        getResourcesNames(getFullPathsToContent(DATA_DIR).dirs);

    auto topLvMenu = Menu(&topLvDirsNames, &selected, option);
    screen.Loop(topLvMenu);

    auto topLvSelectedDirFullPath = 
        DATA_DIR + "/" + topLvDirsNames[selected];

    std::cout << "Selected: " << topLvSelectedDirFullPath << std::endl;
    
    /* first level dir */
    auto firstLvContentNames = 
        getResourcesNames(getFullPathsToContent(topLvSelectedDirFullPath).all);

    selected = 0;

    auto selectedDirMenu = Menu(&firstLvContentNames, &selected, option);
    screen.Loop(selectedDirMenu);

    auto firstLvSelectedDirFullPath = 
        topLvSelectedDirFullPath + "/" + firstLvContentNames[selected];

    std::cout << "Selected: " << firstLvSelectedDirFullPath << std::endl;


    /* xml file interaction */
    std::string myText;
	std::string aLLText;
    std::string name;
    std::string ing;
    std::string description;

    pugi::xml_document doc;
    auto fullPath = ROOT_DIR + firstLvSelectedDirFullPath;
    if (!doc.load_file(fullPath.c_str())) return -1;

    for (pugi::xml_node node: doc)
    {
        for (pugi::xml_node child: node.children())
        {
            auto tag = static_cast<std::string>(child.name());
            auto pt = tagMapping[tag];

            switch(pt) {
                case ParagraphTag::Name: 
                    name = static_cast<std::string>(child.child_value());
                    aLLText += "Name: " + name + "\n";
                    break;
                case ParagraphTag::Ingredient: 
                    ing = static_cast<std::string>(child.child_value("IngredientName"));
                    aLLText += "Ingredient: " + ing + "\n";
                    break;
                case ParagraphTag::Direction: 
                    description = static_cast<std::string>(child.child_value("DirectionText"));
                    aLLText += "Step: " + description + "\n";
                    break;
            }
        }
    }

    /* formating and rendering */
    auto btn_dec_01 = ftxui::Button("Edit", [&] {}, style());
    auto btn_inc_01 = ftxui::Button("Back", [&] {}, style());

    int row = 0;
    auto textarea_1 = ftxui::Input(&aLLText);
     auto buttons = ftxui::Container::Vertical({
        ftxui::Container::Horizontal({btn_dec_01, btn_inc_01}, &row) | ftxui::flex,
        ftxui::Container::Horizontal({textarea_1}, &row) | ftxui::flex,
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