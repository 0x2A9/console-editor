#include <memory>

#include "xml_processors/processor_base.hpp"
#include "pugixml.hpp"

enum ParagraphTag {
  Name = 1,
  Ingredient = 2,
  Direction = 3
};

class RecipesProcessor : public ProcessorBase {
 public:
  RecipesProcessor(std::string path) : ProcessorBase(path) {};

  std::string StringFromXml() override {
    std::string full_text;
    std::string name;
    std::string ingredient;
    std::string description;

    for (pugi::xml_node node: this->doc) {
      for (pugi::xml_node child: node.children()) {
        auto tag = static_cast<std::string>(child.name());
        auto pt = this->mapping[tag];

        switch(pt) {
          case ParagraphTag::Name: 
            name = static_cast<std::string>(child.child_value());
            full_text += "Name: " + name + "\n";
            break;
          case ParagraphTag::Ingredient: 
            ingredient = static_cast<std::string>(child.child_value("IngredientName"));
            full_text += "Ingredient: " + ingredient + "\n";
            break;
          case ParagraphTag::Direction: 
            description = static_cast<std::string>(child.child_value("DirectionText"));
            full_text += "Step: " + description + "\n";
            break;
        }
      }
    }

    return full_text;
  }

  protected:
   std::unordered_map<std::string, ParagraphTag> mapping = {
    { "Name", ParagraphTag::Name },
    { "Ingredient", ParagraphTag::Ingredient },
    { "Direction", ParagraphTag::Direction },
   };
};

std::shared_ptr<ProcessorBase> RecipesProc(std::string path) {
  return std::make_shared<RecipesProcessor>(RecipesProcessor(path));
}
