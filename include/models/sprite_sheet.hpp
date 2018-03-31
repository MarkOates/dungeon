#pragma once



#include <allegro5/allegro.h>
#include <string>
#include <vector>



class SpriteSheet
{
private:
   ALLEGRO_BITMAP *atlas;
   std::vector<ALLEGRO_BITMAP *> sprites;
   int sprite_width;
   int sprite_height;
   int num_rows;
   int num_columns;
   int scale;

   bool _create_sub_sprites();
   void _create_atlas_copy();

public:
   SpriteSheet(std::string filename, int sprite_width=48, int sprite_height=48, int scale=1);
   ~SpriteSheet();

   ALLEGRO_BITMAP *get_sprite(int index);
};



