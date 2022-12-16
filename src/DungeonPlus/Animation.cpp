

#include <DungeonPlus/Animation.hpp>




namespace DungeonPlus
{


Animation::Animation()
   : name("[unset-name]")
   , frames({})
   , playmode(PLAYMODE_UNDEF)
{
}


Animation::~Animation()
{
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


