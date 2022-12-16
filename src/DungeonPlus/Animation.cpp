

#include <DungeonPlus/Animation.hpp>




namespace DungeonPlus
{


Animation::Animation()
   : name("[unset-name]")
   , frames({})
   , playmode(PLAYMODE_UNDEF)
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


