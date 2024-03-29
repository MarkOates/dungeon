


#include <dungeon/models/entities/item_entity.hpp>



ItemEntity::ItemEntity(ElementID *parent, ALLEGRO_BITMAP *bmp, int item_type_int, float x, float y)
   : Entity::Base(parent, "item", x, y)
{
   place.size = { 80, 20 };
   bitmap.bitmap(bmp);
   bitmap.align(0.5, 1.0);
   bitmap.scale(2.0, 2.0);

   set("item_type_int", item_type_int);
}



