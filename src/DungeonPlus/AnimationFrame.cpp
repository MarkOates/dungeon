

#include <DungeonPlus/AnimationFrame.hpp>




namespace DungeonPlus
{


AnimationFrame::AnimationFrame(int index, float duration)
   : index(index)
   , duration(duration)
{
}


AnimationFrame::~AnimationFrame()
{
}


float AnimationFrame::get_duration() const
{
   return duration;
}




} // namespace DungeonPlus


