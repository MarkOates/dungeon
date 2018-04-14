#pragma once


#include <models/entities/entity_base.hpp>
#include <framework/placement2d.hpp>


namespace MotionFX
{
   class Base : public EntityBase
   {
   protected:
      float duration;
      float counter;

   public:
      Base(ElementID *parent, std::string motion_fx_type, float x, float y, float duration);
      virtual ~Base();

      virtual void update();
   };
}


