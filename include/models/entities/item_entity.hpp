#pragma once



#include <models/entities/entity_base.hpp>



class ItemEntity : public EntityBase
{
public:
   ItemEntity(ElementID *parent, ALLEGRO_BITMAP *image, int item_type_num, float x, float y);
};



