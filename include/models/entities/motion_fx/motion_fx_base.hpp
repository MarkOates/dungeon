#pragma once



#include <models/entities/entity_base.hpp>
#include <framework/placement2d.hpp>



class MotionFXBase : public EntityBase
{
protected:
   float duration;
   float counter;

public:
   MotionFXBase(ElementID *parent, std::string motion_fx_type, float x, float y, float duration);
   virtual ~MotionFXBase();

   virtual void update();
   virtual void draw();
};



