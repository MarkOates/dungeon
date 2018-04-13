#pragma once


#include <models/entities/motion_fx/base.hpp>
#include <models/sprite_sheet.hpp>


namespace MotionFX
{
   class FrameAnimation : public Base
   {
   private:
      int current_frame;
      int num_frames;
      float frames_per_second;
      SpriteSheet sprite_sheet;

   public:
      FrameAnimation(ElementID *parent, std::string sprite_sheet_filename, int frame_width, int frame_height, int scale, float x, float y);
      ~FrameAnimation();

      void advance_frame();

      void update() override;
      void draw() override;
   };
}


