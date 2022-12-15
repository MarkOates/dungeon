#ifndef ___AF_BITMAP_OBJECT_HEADER
#define ___AF_BITMAP_OBJECT_HEADER




#include <string>
#include <allegro5/allegro.h>
#include <allegro5/allegro_color.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <dungeon/models/object2d.hpp>
#include <AllegroFlare/Shader.hpp>




class BitmapObject : public object2d
{
private:
   static BitmapObject *dummy;

public:
   ALLEGRO_BITMAP *_bitmap;
   int _flags;

   bool swapping_colors;
   ALLEGRO_COLOR swap_color_0;
   ALLEGRO_COLOR swap_color_1;
   ALLEGRO_COLOR swap_color_2;
   ALLEGRO_COLOR swap_color_3;

   static BitmapObject *get_dummy()
   {
      if (!dummy) dummy = new BitmapObject(NULL);
      return dummy;
   }

public:
   BitmapObject(ALLEGRO_BITMAP *bitmap)
      : object2d(0,0,128,128)
      , _bitmap(bitmap)
      , _flags(0) // previously ALLEGRO_FLAGS_EMPTY
      , swapping_colors(false)
   {
      this->bitmap(_bitmap);
   }
   inline BitmapObject &clean()
   {
      if (_placement) _placement->clear();
      //if (_appearance) _appearance->clear();
      _bitmap = NULL;
      *_h = 128;
      *_w = 128;
      return *this;
   }
   inline BitmapObject &align(float x, float y) { object2d::align(x, y); return *this; }
   inline BitmapObject &position(float x, float y) { object2d::position(x, y); return *this; }
   inline BitmapObject &anchor(float x, float y) { object2d::anchor(x, y); return *this; }
   inline BitmapObject &scale(float x, float y) { object2d::scale(x, y); return *this; }
   inline BitmapObject &scale(float s) { object2d::scale(s); return *this; }
   //inline BitmapObject &opacity(float opacity) { object2d::opacity(opacity); return *this; }
   inline BitmapObject &save(std::string filename) { al_save_bitmap(filename.c_str(), _bitmap); return *this; }
   inline BitmapObject &flags(int flags) { _flags = flags; return *this; }
   ALLEGRO_BITMAP *get_bitmap() { return _bitmap; }
   inline BitmapObject &bitmap(ALLEGRO_BITMAP *bitmap)
   {
      //if (_bitmap == bitmap) return *this; //<- this line is not necessairy, and creates a bug when the object is initialized
      _bitmap = bitmap;
      if (_bitmap)
      {
         *_w = al_get_bitmap_width(_bitmap);
         *_h = al_get_bitmap_height(_bitmap);
      }
      else
      {
         *_w = 10;
         *_h = 10;
      }
      return *this;
   }
   void set_swapping_colors(bool swapping_colors)
   {
      this->swapping_colors = swapping_colors;
   }
   void set_swap_color_0(ALLEGRO_COLOR color)
   {
      swap_color_0 = color;
   }
   void set_swap_color_1(ALLEGRO_COLOR color)
   {
      swap_color_1 = color;
   }
   void set_swap_color_2(ALLEGRO_COLOR color)
   {
      swap_color_2 = color;
   }
   void set_swap_color_3(ALLEGRO_COLOR color)
   {
      swap_color_3 = color;
   }
   inline void send_attributes_to_shader()
   {
      //if (!shader) return;
      if (!swapping_colors) return;

      AllegroFlare::Shader::set_bool("swapping_colors", swapping_colors);
      AllegroFlare::Shader::set_vec4("swap_color_0", swap_color_0.r, swap_color_0.g, swap_color_0.b, swap_color_0.a);
      AllegroFlare::Shader::set_vec4("swap_color_1", swap_color_1.r, swap_color_1.g, swap_color_1.b, swap_color_1.a);
      AllegroFlare::Shader::set_vec4("swap_color_2", swap_color_2.r, swap_color_2.g, swap_color_2.b, swap_color_2.a);
      AllegroFlare::Shader::set_vec4("swap_color_3", swap_color_3.r, swap_color_3.g, swap_color_3.b, swap_color_3.a);
   }
   inline void unset_attributes_to_shader()
   {
      //if (!shader) return;
      if (!swapping_colors) return;

      AllegroFlare::Shader::set_bool("swapping_colors", false);
   }
   inline BitmapObject &draw_raw()
   {
      if (_bitmap)
      {
         //if (_appearance) al_draw_tinted_bitmap(_bitmap, color::color(_appearance->color, _appearance->opacity), 0, 0, _flags);
         //else al_draw_bitmap(_bitmap, 0, 0, _flags);
         al_draw_bitmap(_bitmap, 0, 0, _flags);
      }
      return *this;
   }
   inline BitmapObject &draw()
   {
      if (_placement) _placement->start_transform();
      send_attributes_to_shader();
      draw_raw();
      unset_attributes_to_shader();
      if (_placement) _placement->restore_transform();
      return *this;
   }
};




#endif
