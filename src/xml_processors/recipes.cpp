#include <memory>
#include <map>
#include <string>

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

    this->ParseXml();

    for (auto [index, item]: this->ingredients) {
      this->content += "Ingredient: " + item + "\n";
    }

    for (auto [index, item]: this->steps) {
      this->content += "Step: " + item + "\n";
    }

    return this->content;
  }
  
 protected:
  std::unordered_map<std::string, ParagraphTag> mapping = {
    { "Name", ParagraphTag::Name },
    { "Ingredient", ParagraphTag::Ingredient },
    { "Direction", ParagraphTag::Direction },
  };

  std::map<int, std::string> ingredients;
  std::map<int, std::string> steps;

  void ParseXml() {
    std::string name;
    std::string ingredient;
    int index;
    std::string description;

    for (pugi::xml_node node: this->doc) {
      for (pugi::xml_node child: node.children()) {
        auto tag = static_cast<std::string>(child.name());
        auto pt = this->mapping[tag];

        switch(pt) {
          case ParagraphTag::Name: 
            name = static_cast<std::string>(child.child_value());
            this->content += "Name: " + name + "\n";
            break;
          case ParagraphTag::Ingredient: 
            ingredient = static_cast<std::string>(child.child_value("IngredientName"));
            index = std::stoi(static_cast<std::string>(child.child_value("DisplayOrder")));
            this->ingredients[index] = ingredient;
            break;
          case ParagraphTag::Direction: 
            description = static_cast<std::string>(child.child_value("DirectionText"));
            index = std::stoi(static_cast<std::string>(child.child_value("DisplayOrder")));
            this->steps[index] = description;
            break;
        }
      }
    }
  }

  std::string content;
};

std::shared_ptr<ProcessorBase> RecipesProc(std::string path) {
  return std::make_shared<RecipesProcessor>(RecipesProcessor(path));
}
