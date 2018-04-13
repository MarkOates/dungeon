

#include <models/entities/motion_fx/frame_animation.hpp>


namespace MotionFX
{


FrameAnimation::FrameAnimation(ElementID *parent, std::string sprite_sheet_filename, int frame_width, int frame_height, int scale, float x, float y)
   : Base(parent, "frame_animation", x, y, 0)
   , current_frame(-1)
   , num_frames(0)
   , frames_per_second(12.0)
   , sprite_sheet(sprite_sheet_filename, frame_width, frame_height, scale)
{
   num_frames = sprite_sheet.get_num_sprites();
   bitmap.position(0, 0)
      .align(0.5, 1.0)
      .color(color::white);
}


FrameAnimation::~FrameAnimation()
{
}


void FrameAnimation::advance_frame()
{
   current_frame++;
   bitmap.bitmap(sprite_sheet.get_sprite(current_frame));
}


void FrameAnimation::update()
{
   counter -= 1.0 / 60.0;
   if (counter <= 0)
   {
      advance_frame();

      if (current_frame >= num_frames) flag_for_deletion();
      else counter = 1.0 / frames_per_second;
   }
}


void FrameAnimation::draw()
{
   place.start_transform();
   bitmap.draw();
   place.restore_transform();
}


}


