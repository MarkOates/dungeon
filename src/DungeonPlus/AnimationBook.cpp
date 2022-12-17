

#include <DungeonPlus/AnimationBook.hpp>

#include <DungeonPlus/ASESpriteSheetJSONDataLoader.hpp>
#include <DungeonPlus/Errors.hpp>
#include <iostream>
#include <sstream>
#include <stdexcept>


namespace DungeonPlus
{


AnimationBook::AnimationBook(SpriteSheet* sprite_sheet)
   : sprite_sheet(sprite_sheet)
   , dictionary({})
   , initialized(false)
{
}


AnimationBook::~AnimationBook()
{
}


void AnimationBook::set_dictionary(std::map<std::string, DungeonPlus::Animation> dictionary)
{
   this->dictionary = dictionary;
}


SpriteSheet* AnimationBook::get_sprite_sheet()
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[AnimationBook::get_sprite_sheet]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("AnimationBook::get_sprite_sheet: error: guard \"initialized\" not met");
   }
   return sprite_sheet;
}

void AnimationBook::init()
{
   if (!((!initialized)))
   {
      std::stringstream error_message;
      error_message << "[AnimationBook::init]: error: guard \"(!initialized)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("AnimationBook::init: error: guard \"(!initialized)\" not met");
   }
   // build the sprite sheet

   ALLEGRO_BITMAP *sprite_sheet_bitmap = al_load_bitmap("./bin/data/bitmaps/sprites_grid-x.png");
   sprite_sheet = new SpriteSheet(sprite_sheet_bitmap, 48, 48, 8); // auto-inits
   al_destroy_bitmap(sprite_sheet_bitmap);

   // load the data

   DungeonPlus::ASESpriteSheetJSONDataLoader loader(sprite_sheet);
   dictionary = loader.load();

   initialized = true;
   return;
}

DungeonPlus::Animation AnimationBook::get_animation_by_name(std::string name)
{
   if (dictionary.count(name) == 0)
   {
      std::stringstream error_message;
      error_message << "No animation exists for name \"" << name << "\"";
      DungeonPlus::Errors::throw_error("DungeonPlus::AnimationBook::get_animation_by_name", error_message.str());
   }
   return dictionary[name];
}

void AnimationBook::_build_placeholder_dictionary()
{
   dictionary =  {
      { "blob", DungeonPlus::Animation(sprite_sheet, "blob", std::vector<DungeonPlus::AnimationFrame>{
            { 1, 0.200f },
            { 2, 0.100f },
            { 3, 0.200f },
         }, DungeonPlus::Animation::PLAYMODE_FORWARD_PING_PONG
      )},
   };
   return;
}


} // namespace DungeonPlus


