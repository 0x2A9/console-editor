#include "xml_processors/processor_base.hpp"

#include <memory>
#include <map>
#include <string>

#include "pugixml.hpp"

enum ParagraphTag {
  kName = 1,
  kIngredient = 2,
  kDirection = 3
};

class RecipesProcessor : public ProcessorBase {
 public:
  explicit RecipesProcessor(const std::string &path) : ProcessorBase(path) {};

  std::string StringFromXml() override {
    std::string full_text;

    this->ParseXml();

    for (auto [index, item]: this->ingredients_) {
      this->content_ += "Ingredient: " + item + "\n";
    }

    for (auto [index, item]: this->steps_) {
      this->content_ += "Step: " + item + "\n";
    }

    return this->content_;
  }

 protected:
  void ParseXml() {
      std::string name;
      std::string ingredient;
      int index;
      std::string description;
  
      for (pugi::xml_node node: this->doc_) {
          for (pugi::xml_node child: node.children()) {
              auto tag = static_cast<std::string>(child.name());
              auto pt = this->mapping_[tag];
  
              switch(pt) {
                  case ParagraphTag::kName:
                      name = static_cast<std::string>(child.child_value());
                      this->content_ += "Name: " + name + "\n";
                      break;
                  case ParagraphTag::kIngredient:
                      ingredient = static_cast<std::string>(child.child_value("IngredientName"));
                      index = std::stoi(static_cast<std::string>(child.child_value("DisplayOrder")));
                      this->ingredients_[index] = ingredient;
                      break;
                  case ParagraphTag::kDirection:
                      description = static_cast<std::string>(child.child_value("DirectionText"));
                      index = std::stoi(static_cast<std::string>(child.child_value("DisplayOrder")));
                      this->steps_[index] = description;
                      break;
              }
          }
      }
  }

  std::unordered_map<std::string, ParagraphTag> mapping_ = {
    { "Name", ParagraphTag::kName },
    { "Ingredient", ParagraphTag::kIngredient },
    { "Direction", ParagraphTag::kDirection },
  };

  std::map<int, std::string> ingredients_;
  std::map<int, std::string> steps_;
  std::string content_;
};

std::shared_ptr<ProcessorBase> RecipesProc(std::string path) {
  return std::make_shared<RecipesProcessor>(RecipesProcessor(path));
}
