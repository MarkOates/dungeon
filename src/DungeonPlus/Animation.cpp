

#include <DungeonPlus/Animation.hpp>

#include <cmath>


namespace DungeonPlus
{


Animation::Animation(SpriteSheet* sprite_sheet, std::string name, std::vector<AnimationFrame> frames, uint32_t playmode)
   : sprite_sheet(sprite_sheet)
   , name(name)
   , frames(frames)
   , playmode(playmode)
   , playhead(0.0f)
{
}


Animation::~Animation()
{
}


void Animation::start()
{
   playhead = 0.0f;
   return;
}

void Animation::update()
{
   const float FRAME_INCREMENT = 1.0f/60.0f;
   playhead += FRAME_INCREMENT;
   return;
}

void Animation::draw()
{
   ALLEGRO_BITMAP *bitmap = get_frame_at(playhead);
   if (!bitmap) return;
   al_draw_bitmap(bitmap, 0, 0, 0);
   return;
}

uint32_t Animation::get_frame_id_at(float time)
{
   switch(playmode)
   {
      case PLAYMODE_FORWARD_ONCE: {
         float duration_so_far = 0.0f;
         for (auto &frame : frames)
         {
            duration_so_far += frame.get_duration();
            if (playhead < duration_so_far) return frame.get_index();
         }
      } break;

      case PLAYMODE_FORWARD_LOOP: {
         float duration_so_far = 0.0f;
         float duration = calculate_duration();
         float looped_playhead = fmod(playhead, duration);
         for (auto &frame : frames)
         {
            duration_so_far += frame.get_duration();
            if (looped_playhead < duration_so_far) return frame.get_index();
         }
      } break;
   }
   return 0;
}

ALLEGRO_BITMAP* Animation::get_frame_at(float time)
{
   uint32_t cell_id = get_frame_id_at(time);
   return sprite_sheet->get_cell(cell_id);
}

float Animation::calculate_duration()
{
   float result = 0.0f;
   for (auto &frame : frames)
   {
      result += frame.get_duration();
   }
   return result;
}


} // namespace DungeonPlus


