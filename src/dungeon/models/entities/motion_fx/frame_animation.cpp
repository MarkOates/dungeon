

#include <dungeon/models/entities/motion_fx/frame_animation.hpp>


#include <AllegroFlare/Color.hpp>


namespace MotionFX
{


FrameAnimation::FrameAnimation(AllegroFlare::ElementID *parent, ALLEGRO_BITMAP *sprite_sheet_bitmap, int frame_width, int frame_height, int scale, float x, float y)
   : Base(parent, "frame_animation", x, y, 0)
   , sprite_sheet(sprite_sheet_bitmap, frame_width, frame_height, scale)
   , frames_per_second(12.0)
   , num_frames(sprite_sheet.get_num_sprites())
   , current_frame(-1)
{
   bitmap.position(0, 0)
      .align(0.5, 1.0);
      //.color(AllegroFlare::color::white); // NOTE: COLOR HERE
}


FrameAnimation::~FrameAnimation()
{
}


void FrameAnimation::set_frames_per_second(float fps)
{
   this->frames_per_second = fps;
}


float FrameAnimation::get_frames_per_second()
{
   return frames_per_second;
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


