

#include <dungeon/models/entities/bookshelf_entity.hpp>


BookshelfEntity::BookshelfEntity(ElementID *parent, ALLEGRO_BITMAP *al_bitmap, float x, float y)
   : Entity::Base(parent, "bookshelf", x, y)
{
   bitmap
      .bitmap(al_bitmap)
      .scale(2, 2)
      .align(0.5, 1.0);

   place.size = vec2d(48, 16);
}


BookshelfEntity::~BookshelfEntity()
{
}


void BookshelfEntity::on_interaction()
{
}


void BookshelfEntity::draw()
{
   place.start_transform();
   al_draw_filled_rectangle(0, 0, place.size.x, place.size.y, color::purple);
   place.restore_transform();
   Entity::Base::draw();
}


