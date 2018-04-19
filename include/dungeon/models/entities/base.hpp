#pragma once


#include <framework/objects/bitmap_object.hpp>
#include <framework/placement2d.hpp>
#include <framework/element_id.hpp>


namespace Entity
{
   class Base : public ElementID
   {
   public:
      placement2d place;
      placement2d velocity;
      BitmapObject bitmap;

      Base(ElementID *parent, std::string type, float x, float y);
      virtual ~Base();

      virtual void update();
      virtual void draw();

      void flag_for_deletion();
      bool collides(const Base &other);
   };
}


