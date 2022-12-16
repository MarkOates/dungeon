#pragma once


#include <DungeonPlus/AnimationFrame.hpp>
#include <string>
#include <vector>


namespace DungeonPlus
{
   class Animation
   {
   private:
      std::string name;
      std::vector<AnimationFrame> frames;
      int playmode;

   protected:


   public:
      Animation();
      ~Animation();

      float calculate_duration();
   };
}



