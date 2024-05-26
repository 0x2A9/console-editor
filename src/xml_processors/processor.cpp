#include <string>

#include "xml_processors/processor_base.hpp"

ProcessorBase::ProcessorBase(const std::string &path) {
  this->doc.load_file(path.c_str());
}
