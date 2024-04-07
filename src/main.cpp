#include <string>    
#include <vector>    
#include <iostream>
#include <functional>
 
#include "ftxui/component/captured_mouse.hpp"
#include "ftxui/component/component.hpp"           
#include "ftxui/component/component_options.hpp"   
#include "ftxui/component/screen_interactive.hpp"  

#include "utils/fs.h"
 
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
}