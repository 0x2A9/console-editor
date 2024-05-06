#ifndef UI_H
#define UI_H

#include "ftxui/component/component.hpp"    
#include "ftxui/component/screen_interactive.hpp" 

ftxui::ButtonOption ButtonStyle();
ftxui::InputOption InputStyle();
ftxui::Component CreateExitButton(std::string name, ftxui::ScreenInteractive &screen);
void CreateForm(std::string *data, ftxui::Components cmps, ftxui::ScreenInteractive &screen);

#endif // UI_H
