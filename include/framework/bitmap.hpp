#pragma once



#include <allegro5/allegro.h>
#include <allegro5/allegro_color.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <framework/appearance2d.hpp>
#include <framework/placement2d.hpp>
#include <framework/useful.hpp>
#include <iostream>
#include <string>



class Bitmap : public placement2d
{
public:
   ALLEGRO_BITMAP *al_bitmap;
   ALLEGRO_COLOR color;
   float opacity;
   int _flags;

public:
   Bitmap(ALLEGRO_BITMAP *al_bitmap, float x, float y)
      : placement2d(x, y, 0, 0, 0, 1.0, 1.0, 0.0, 0.0, 0.0, 0.0)
      , al_bitmap(al_bitmap)
      , color(color::white)
      , opacity(1.0)
      , _flags(ALLEGRO_FLAGS_EMPTY)
   {
      this->bitmap(al_bitmap);
   }
   //inline Bitmap &opacity(float opacity) { opacity(opacity); return *this; }
   //inline Bitmap &save(std::string filename) { al_save_bitmap(filename.c_str(), al_bitmap); return *this; }
   inline Bitmap &flags(int flags) { _flags = flags; return *this; }
   ALLEGRO_BITMAP *get_bitmap() { return al_bitmap; }
   inline Bitmap &bitmap(ALLEGRO_BITMAP *bitmap)
   {
      al_bitmap = bitmap;
      if (al_bitmap)
      {
         w = al_get_bitmap_width(al_bitmap);
         h = al_get_bitmap_height(al_bitmap);
      }
      else
      {
         w = 1;
         h = 1;
      }
      return *this;
   }
   inline Bitmap &draw_raw()
   {
      if (al_bitmap)
      {
         al_draw_tinted_bitmap(al_bitmap, ::color::color(color, opacity), 0, 0, _flags);
      }
      return *this;
   }
   inline Bitmap &draw()
   {
      start_transform();
      draw_raw();
      restore_transform();
      //draw_crosshair(x, y);
      return *this;
   }
};




