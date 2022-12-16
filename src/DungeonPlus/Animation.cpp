

#include <DungeonPlus/Animation.hpp>




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


void Animation::update()
{
   const float FRAME_INCREMENT = 1.0f/60.0f;
   playhead += FRAME_INCREMENT;
   return;
}

uint32_t Animation::get_frame_id_at(float time)
{
   float duration_so_far = 0.0f;
   for (auto &frame : frames)
   {
      if (frame.get_duration() > duration_so_far) return frame.get_index();
      duration_so_far += frame.get_duration();
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


