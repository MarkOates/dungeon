

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
   , finished(false)
{
}


Animation::~Animation()
{
}


uint32_t Animation::get_playmode() const
{
   return playmode;
}


std::vector<AnimationFrame> &Animation::get_frames_ref()
{
   return frames;
}


void Animation::start()
{
   playhead = 0.0f;
   finished = false;
   return;
}

void Animation::update()
{
   const float FRAME_INCREMENT = 1.0f/60.0f;
   playhead += FRAME_INCREMENT;

   // update "finished"
   switch(playmode)
   {
      case PLAYMODE_FORWARD_ONCE:
        if (playhead > calculate_duration()) finished = true;
      break;

      case PLAYMODE_FORWARD_LOOP:
        // NOTE: nothing to do, FORWARD_LOOP plays indefinitely
      break;

      case PLAYMODE_FORWARD_PING_PONG:
        // NOTE: nothing to do, PING_PONG plays indefinitely
      break;
   }
   return;
}

void Animation::draw()
{
   ALLEGRO_BITMAP *bitmap = get_frame_at(playhead);
   if (!bitmap) return;
   al_draw_bitmap(bitmap, 0, 0, 0);
   return;
}

int Animation::get_num_frames()
{
   return frames.size();
}

ALLEGRO_BITMAP* Animation::get_frame_now()
{
   return get_frame_at(playhead);
}

uint32_t Animation::get_frame_id_now()
{
   return get_frame_id_at(playhead);
}

uint32_t Animation::get_frame_id_at(float time)
{
   // NOTE: no guard logic for when duration is 0.0

   switch(playmode)
   {
      case PLAYMODE_FORWARD_ONCE: {
         float duration_so_far = 0.0f;
         for (auto &frame : frames)
         {
            duration_so_far += frame.get_duration();
            if (time < duration_so_far) return frame.get_index();
         }
      } break;

      case PLAYMODE_FORWARD_LOOP: {
         float duration_so_far = 0.0f;
         float duration = calculate_duration();
         float looped_playhead = fmod(time, duration);
         for (auto &frame : frames)
         {
            duration_so_far += frame.get_duration();
            if (looped_playhead < duration_so_far) return frame.get_index();
         }
      } break;

      case PLAYMODE_FORWARD_PING_PONG: {
         float duration_so_far = 0.0f;
         float duration = calculate_duration();
         float ping_pong_playhead = fmod(time, duration*2);
         if (ping_pong_playhead > duration) ping_pong_playhead = duration*2 - ping_pong_playhead;
         for (auto &frame : frames)
         {
            duration_so_far += frame.get_duration();
            if (ping_pong_playhead < duration_so_far) return frame.get_index();
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


