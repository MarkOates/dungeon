#pragma once


#include <allegro5/allegro.h>


namespace TransitionFX
{
   class Base
   {
   private:
      ALLEGRO_BITMAP *display_bitmap;
      ALLEGRO_BITMAP *surface_A;
      ALLEGRO_BITMAP *surface_B;
      float duration;
      float position;
      bool finished;

   public:
      Base(ALLEGRO_BITMAP *display_bitmap);
      ~Base();

      ALLEGRO_BITMAP *get_surface_A();
      ALLEGRO_BITMAP *get_surface_B();

      virtual void update();
      virtual void draw();
   };
}


