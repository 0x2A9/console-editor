#ifndef CONSOLE_EDITOR_MANAGERS_RENDER_MANAGER_HPP
#define CONSOLE_EDITOR_MANAGERS_RENDER_MANAGER_HPP

#include "ftxui/component/component.hpp"
#include "ftxui/component/screen_interactive.hpp"

class RenderManager {
 public:
  RenderManager() = default;
  void Process();

 private:
  ftxui::ScreenInteractive screen_ = ftxui::ScreenInteractive::TerminalOutput();
  int sel_ = 0;
};

#endif // CONSOLE_EDITOR_MANAGERS_RENDER_MANAGER_HPP
