#ifndef CONSOLE_EDITOR_XML_PROCESSORS_PROCESSOR_HPP
#define CONSOLE_EDITOR_XML_PROCESSORS_PROCESSOR_HPP

#include "processor_base.hpp"

#include <memory>

std::shared_ptr<ProcessorBase> RecipesProc(std::string path);

#endif // CONSOLE_EDITOR_XML_PROCESSORS_PROCESSOR_HPP
