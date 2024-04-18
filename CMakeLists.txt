cmake_minimum_required (VERSION 3.11)
 
include(FetchContent)
set(FETCHCONTENT_UPDATES_DISCONNECTED TRUE)
FetchContent_Declare(ftxui
  GIT_REPOSITORY https://github.com/ArthurSonzogni/ftxui
  GIT_TAG v5.0.0 
)
FetchContent_Declare(pugixml
  GIT_REPOSITORY https://github.com/zeux/pugixml
  GIT_TAG v1.14
)
FetchContent_MakeAvailable(ftxui pugixml)
 
project(console-editor LANGUAGES CXX VERSION 1.0.0)
add_executable(
  console-editor 
  src/main.cpp 
  src/utils/fs.cpp
)
target_link_libraries(console-editor
  PRIVATE ftxui::screen
  PRIVATE ftxui::dom
  PRIVATE ftxui::component 
  pugixml
)
