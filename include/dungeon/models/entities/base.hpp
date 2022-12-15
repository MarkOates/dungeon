#pragma once


//#include <framework/objects/bitmap_object.hpp>
//#include <framework/placement2d.hpp>
//#include <framework/element_id.hpp>

#include <AllegroFlare/ElementID.hpp>
#include <AllegroFlare/Placement2D.hpp>
#include <AllegroFlare/EventEmitter.hpp>

#include <dungeon/models/bitmap_object.hpp>


namespace Entity
{
   class Base : public AllegroFlare::ElementID
   {
   public:
      AllegroFlare::Placement2D place;
      AllegroFlare::Placement2D velocity;
      BitmapObject bitmap;

      Base(AllegroFlare::ElementID *parent, std::string type, float x, float y);
      virtual ~Base();

      virtual void update();
      virtual void draw();

      void flag_for_deletion();
      bool collides(Base &other);
   };
}


