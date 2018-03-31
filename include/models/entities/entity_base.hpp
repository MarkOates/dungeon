#pragma once



#include <framework/objects/bitmap_object.hpp>
#include <framework/placement2d.hpp>
#include <framework/element_id.hpp>



class EntityBase : public ElementID
{
public:
   placement2d place;
   placement2d velocity;
   BitmapObject bitmap;

   EntityBase(ElementID *parent, std::string type, float x, float y);
   virtual ~EntityBase();

   virtual void update();
   virtual void draw();

   void flag_for_deletion();
   bool collides(const EntityBase &other);
};



