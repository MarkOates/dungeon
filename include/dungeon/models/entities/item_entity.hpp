#pragma once


#include <dungeon/models/entities/base.hpp>


class ItemEntity : public Entity::Base
{
public:
   ItemEntity(ElementID *parent, ALLEGRO_BITMAP *image, int item_type_num, float x, float y);
};


