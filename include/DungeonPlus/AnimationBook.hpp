#pragma once


#include <DungeonPlus/Animation.hpp>
#include <allegro5/allegro.h>
#include <dungeon/models/sprite_sheet.hpp>
#include <map>
#include <string>


namespace DungeonPlus
{
   class AnimationBook
   {
   private:
      std::string png_source_filename;
      std::string json_source_filename;
      SpriteSheet* sprite_sheet;
      std::map<std::string, DungeonPlus::Animation> dictionary;
      bool initialized;
      void _build_placeholder_dictionary();

   protected:


   public:
      AnimationBook(std::string png_source_filename="./bin/data/bitmaps/sprites_grid-x.png", std::string json_source_filename="./bin/data/bitmaps/sprites_grid-x.json");
      ~AnimationBook();

      void set_dictionary(std::map<std::string, DungeonPlus::Animation> dictionary);
      SpriteSheet* get_sprite_sheet();
      void init();
      ALLEGRO_BITMAP* get_first_frame(std::string tag_name="[unset-tag_name]");
      DungeonPlus::Animation get_animation_by_name(std::string name="[unset-name]");
   };
}



