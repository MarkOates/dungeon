#pragma once


namespace TransitionFX
{
   class Crossfade
   {
   public:
      Crossfade(ALLEGRO_BITMAP *display_bitmap);
      ~Crossfade();

      void is_finished();

      void update() override;
      void draw() override;
   };
};


