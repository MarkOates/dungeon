#pragma once


#include <DungeonPlus/Animation.hpp>
#include <dungeon/models/sprite_sheet.hpp>
#include <map>
#include <string>


namespace DungeonPlus
{
   class AnimationBook
   {
   private:
      SpriteSheet* sprite_sheet;
      std::map<std::string, DungeonPlus::Animation> dictionary;
      bool initialized;
      void _build_dictionary();

   protected:


   public:
      AnimationBook(SpriteSheet* sprite_sheet=nullptr);
      ~AnimationBook();

      void init();
      DungeonPlus::Animation get_animation_by_name(std::string name="[unset-name]");
   };
}



