#include "xml_processors/processor_base.hpp"

#include <string>

ProcessorBase::ProcessorBase(const std::string &path) {
  this->doc_.load_file(path.c_str());
}
