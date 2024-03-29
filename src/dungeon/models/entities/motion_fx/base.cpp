

#include <dungeon/models/entities/motion_fx/base.hpp>


namespace MotionFX
{


Base::Base(AllegroFlare::ElementID *parent, std::string motion_fx_type, float x, float y, float duration)
   : Entity::Base(parent, "motion_fx", x, y)
   , duration(duration)
   , counter(duration)
{
   set("motion_fx_type", motion_fx_type);
}


Base::~Base() {}


void Base::update()
{
   counter -= 1.0 / 60.0;
   if (counter <= 0) flag_for_deletion();
}


} // namespace MotionFX


