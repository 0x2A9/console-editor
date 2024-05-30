#ifndef CONSOLE_EDITOR_UTILS_UI_HPP
#define CONSOLE_EDITOR_UTILS_UI_HPP

#include "ftxui/component/component.hpp"    
#include "ftxui/component/screen_interactive.hpp" 

ftxui::ButtonOption ButtonStyle();
ftxui::InputOption InputStyle();
ftxui::MenuOption MenuStyle(ftxui::ScreenInteractive &screen);
ftxui::Component CreateExitButton(const std::string &name,
                                  ftxui::ScreenInteractive &screen);

void CreateForm(std::string *data,
                const ftxui::Components &cmps,
                ftxui::ScreenInteractive &screen);

#endif // CONSOLE_EDITOR_UTILS_UI_HPP
