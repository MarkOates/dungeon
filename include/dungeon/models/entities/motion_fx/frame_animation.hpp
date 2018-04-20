#pragma once


#include <dungeon/models/entities/motion_fx/base.hpp>
#include <dungeon/models/sprite_sheet.hpp>


namespace MotionFX
{
   class FrameAnimation : public MotionFX::Base
   {
   private:
      SpriteSheet sprite_sheet;
      float frames_per_second;
      int num_frames;
      int current_frame;

   public:
      FrameAnimation(ElementID *parent, std::string sprite_sheet_filename, int frame_width, int frame_height, int scale, float x, float y);
      ~FrameAnimation();

      void set_frames_per_second(float fps);
      float get_frames_per_second();

      void advance_frame();

      void update() override;
      void draw() override;
   };
}


