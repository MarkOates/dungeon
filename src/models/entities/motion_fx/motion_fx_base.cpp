


#include <models/entities/motion_fx/motion_fx_base.hpp>



MotionFXBase::MotionFXBase(ElementID *parent, std::string motion_fx_type, float x, float y, float duration)
   : EntityBase(parent, "motion_fx", x, y)
   , duration(duration)
   , counter(duration)
{
   set("motion_fx_type", motion_fx_type);
}



MotionFXBase::~MotionFXBase() {}



void MotionFXBase::update()
{
   counter -= 1.0 / 60.0;
   if (counter <= 0) flag_for_deletion();
}



void MotionFXBase::draw() {}



