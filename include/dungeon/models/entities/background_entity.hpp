#pragma once


#include <dungeon/models/entities/base.hpp>


class BackgroundEntity : public Entity::Base
{
private:
   ALLEGRO_BITMAP *al_bitmap;

public:
   BackgroundEntity(ElementID *parent, ALLEGRO_BITMAP *al_bitmap, float x, float y);
   ~BackgroundEntity();

   void draw() override;
};


