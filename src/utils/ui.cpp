#include "utils/fs.hpp"

#include "ftxui/component/component.hpp"
#include "ftxui/component/screen_interactive.hpp"

ftxui::ButtonOption ButtonStyle() {
  auto option = ftxui::ButtonOption::Animated();
  option.transform = [](const ftxui::EntryState &s) {
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

ftxui::MenuOption MenuStyle(ftxui::ScreenInteractive &screen) {
  ftxui::MenuOption option;
  option.on_enter = screen.ExitLoopClosure();
  return option;
}

ftxui::Component CreateExitButton(const std::string &name,
                                  ftxui::ScreenInteractive &screen) {
  return ftxui::Button(name, [&screen] { 
    screen.Exit(); 
  }, ButtonStyle());
}

void CreateForm(std::string *data,
                const ftxui::Components &cmps,
                ftxui::ScreenInteractive &screen) {
  int row = 0;

  auto input = ftxui::Input(data, InputStyle());

  auto form = ftxui::Container::Vertical({
    ftxui::Container::Horizontal(cmps, &row) | ftxui::flex,
    ftxui::Container::Horizontal({input}, &row) | 
    ftxui::flex | 
    ftxui::vscroll_indicator | 
    ftxui::frame | 
    ftxui::size(ftxui::HEIGHT, ftxui::LESS_THAN, 25),
  });

  auto comp = ftxui::Renderer(form, [&form] {
    return ftxui::vbox({
      ftxui::text("Choose the action:"),
      ftxui::separator(),
      form->Render() | ftxui::flex,
    }) |
    ftxui::flex | ftxui::border;
  });

  screen.Loop(comp);
}
