


#include <dungeon/models/entities/base.hpp>


#include <allegro5/allegro_primitives.h>
#include <AllegroFlare/Color.hpp>



namespace Entity
{



Base::Base(AllegroFlare::ElementID *parent, std::string type, float x, float y)
   : AllegroFlare::ElementID(parent)
   , place(x, y, 1, 1)
   , velocity()
   , bitmap(nullptr)
{
   set("type", type);
   velocity.scale = { 0, 0 };
   velocity.align = { 0, 0 };
}



Base::~Base()
{}



void Base::update()
{}



void Base::flag_for_deletion()
{
   set("can_be_deleted");
}



void Base::draw()
{
   place.start_transform();
   al_draw_filled_rectangle(0, 0, place.size.x, place.size.y, AllegroFlare::color::red);
   bitmap.position(place.size.x/2, place.size.y/2);
   bitmap.draw();
   place.restore_transform();
}



bool Base::collides(Base &other)
{
   //float h_width = place.size.x * 0.5;
   //float h_height = place.size.y * 0.5;

   // this will not account for rotation or anything fancy.
   // it's an unofficial ballpark close enough for jazz doodad:

   return place.collide(other.place);
   //return other.place.collide(place.x, place.y, h_height, h_width, h_height, h_width);
}



} // namespace Entity



