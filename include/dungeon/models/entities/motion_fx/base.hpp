#pragma once


#include <dungeon/models/entities/base.hpp>
#include <framework/placement2d.hpp>


namespace MotionFX
{
   class Base : public Entity::Base
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


