

#include <DungeonPlus/AnimationBook.hpp>

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


void AnimationBook::init()
{
   if (!((!initialized)))
   {
      std::stringstream error_message;
      error_message << "[AnimationBook::init]: error: guard \"(!initialized)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("AnimationBook::init: error: guard \"(!initialized)\" not met");
   }
   ALLEGRO_BITMAP *sprite_sheet_bitmap = al_load_bitmap("./bin/data/bitmaps/sprites_grid-x.png");
   sprite_sheet = new SpriteSheet(sprite_sheet_bitmap, 48, 48, 8); // auto-inits
   al_destroy_bitmap(sprite_sheet_bitmap);
   _build_dictionary();
   initialized = true;
   return;
}

void AnimationBook::_build_dictionary()
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

DungeonPlus::Animation AnimationBook::get_animation_by_name(std::string name)
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[AnimationBook::get_animation_by_name]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("AnimationBook::get_animation_by_name: error: guard \"initialized\" not met");
   }
   // TODO: guard for exists
   return dictionary[name];
}


} // namespace DungeonPlus


