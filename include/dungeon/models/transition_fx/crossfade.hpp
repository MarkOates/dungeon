#pragma once


#include <dungeon/models/transition_fx/base.hpp>


namespace TransitionFX
{
   class Crossfade : public Base
   {
   public:
      Crossfade(ALLEGRO_BITMAP *display_bitmap);
      ~Crossfade();

      void is_finished();

      void update() override;
      void draw() override;
   };
};


