#ifndef PROCESSOR_H
#define PROCESSOR_H

#include <memory>

#include "processor_base.hpp"

std::shared_ptr<ProcessorBase> RecipesProc(std::string path);

#endif // PROCESSOR_H
