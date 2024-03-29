


#include <dungeon/models/entities/background_entity.hpp>



BackgroundEntity::BackgroundEntity(ElementID *parent, ALLEGRO_BITMAP *al_bitmap, float x, float y)
   : Entity::Base(parent, "background", x, y)
{
   place.align = { 0.0, 0.0 };
   bitmap.bitmap(al_bitmap);
}



BackgroundEntity::~BackgroundEntity()
{}



void BackgroundEntity::draw()
{
   place.start_transform();
   bitmap.draw();
   place.restore_transform();
}



