#ifndef PROCESSOR_BASE_H
#define PROCESSOR_BASE_H

#include <string>      
#include <functional>

#include "pugixml.hpp"

class ProcessorBase {
 public:
  ProcessorBase(std::string path);

  virtual std::string StringFromXml() = 0;

 protected:
  pugi::xml_document doc;
};

#endif // PROCESSOR_BASE_H
