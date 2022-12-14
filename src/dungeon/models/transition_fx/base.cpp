

#include <dungeon/models/transition_fx/base.hpp>

//#include <framework/color.hpp>


namespace TransitionFX
{


Base::Base(ALLEGRO_BITMAP *display_bitmap)
   : display_bitmap(display_bitmap)
   , surface_A(al_create_bitmap(al_get_bitmap_width(display_bitmap), al_get_bitmap_height(display_bitmap)))
   , surface_B(al_create_bitmap(al_get_bitmap_width(display_bitmap), al_get_bitmap_height(display_bitmap)))
   , duration(0)
   , position(0)
   , finished(false)
{
}


Base::~Base()
{
}


void Base::update()
{
   position += 1.0 / 60.0;
   if (position >= duration) finished = true;
}


void Base::draw()
{
   float alpha = 1.0 - (duration - position) / duration;
   al_set_target_bitmap(display_bitmap);
   al_draw_bitmap(surface_A, 0, 0, 0);
   al_draw_tinted_bitmap(surface_B, color::color(color::white, alpha), 0, 0, 0);
}


} // namespace TransitionFX


