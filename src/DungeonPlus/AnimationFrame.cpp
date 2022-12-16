

#include <DungeonPlus/AnimationFrame.hpp>




namespace DungeonPlus
{


AnimationFrame::AnimationFrame(uint32_t index, float duration)
   : index(index)
   , duration(duration)
{
}


AnimationFrame::~AnimationFrame()
{
}


uint32_t AnimationFrame::get_index() const
{
   return index;
}


float AnimationFrame::get_duration() const
{
   return duration;
}




} // namespace DungeonPlus


