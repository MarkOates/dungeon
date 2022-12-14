#pragma once


#include <dungeon/models/entities/base.hpp>


class BookshelfEntity : public Entity::Base
{
private:
   ALLEGRO_BITMAP *al_bitmap;

public:
   BookshelfEntity(ElementID *parent, ALLEGRO_BITMAP *al_bitmap, float x, float y);
   ~BookshelfEntity();

   void on_interaction();
   void draw() override;
};


