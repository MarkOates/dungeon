

#include <DungeonPlus/ASESpriteSheetJSONDataLoader.hpp>

#include <AllegroFlare/UsefulPHP.hpp>
#include <lib/nlohmann/json.hpp>


namespace DungeonPlus
{


ASESpriteSheetJSONDataLoader::ASESpriteSheetJSONDataLoader()
{
}


ASESpriteSheetJSONDataLoader::~ASESpriteSheetJSONDataLoader()
{
}


std::string ASESpriteSheetJSONDataLoader::load()
{
   std::string filename = "./bin/data/bitmaps/sprites_grid-x.json";
   nlohmann::json parsed_json = nlohmann::json::parse(AllegroFlare::php::file_get_contents(filename));

   if (!parsed_json.contains("frames"))
   {
      // TODO throw
   }
   if (!parsed_json.contains("meta"))
   {
      // TODO throw
   }
   if (!parsed_json["meta"].contains("tags"))
   {
      // TODO throw
   }

   // TODO validate frames

   nlohmann::json tags = parsed_json["meta"]["frameTags"];

   for (auto &tag : tags)
   {
      std::string tag_name; // = tag["name"].get_as
      tag.at("name").get_to(tag_name);
      std::cout << "tag name: " << tag_name << std::endl;
   }


   //return "Hello World!";
}


} // namespace DungeonPlus


