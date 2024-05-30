#ifndef CONSOLE_EDITOR_XML_PROCESSORS_PROCESSOR_BASE_HPP
#define CONSOLE_EDITOR_XML_PROCESSORS_PROCESSOR_BASE_HPP

#include <string>      
#include <functional>

#include "pugixml.hpp"

class ProcessorBase {
 public:
  explicit ProcessorBase(const std::string &path);

  virtual std::string StringFromXml() = 0;

 protected:
  pugi::xml_document doc_;
};

#endif // CONSOLE_EDITOR_XML_PROCESSORS_PROCESSOR_BASE_HPP
