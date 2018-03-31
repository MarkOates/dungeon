#pragma once



#include <framework/objects/bitmap_object.hpp>
#include <models/inventory.hpp>
#include <models/naughty_list.hpp>
#include <models/sprite_sheet.hpp>



class HUD
{
private:
   enum mode_t
   {
      MODE_GAME_PLAY,
      MODE_CINEMA
   };

   Inventory *player_inventory;
   NaughtyList *naughty_list;
   int player_health;
   int player_max_health;

   mode_t mode;
   void set_mode(mode_t new_mode);
   BitmapObject chrome_bitmap;
   ALLEGRO_FONT *font;
   ALLEGRO_FONT *font_bigger;
   SpriteSheet sprite_sheet;
   BitmapObject weapon_bitmap;
   BitmapObject shield_bitmap;
   BitmapObject item_bitmap;
   float black_bar_counter;

public:
   HUD(Inventory *player_inventory, NaughtyList *naughty_list);

   void set_values(int player_health, int player_max_health);
   void set_weapon(ALLEGRO_BITMAP *bmp);
   void set_shield(ALLEGRO_BITMAP *bmp);
   void set_item(ALLEGRO_BITMAP *bmp);

   void update();
   void draw();

   void set_to_cinema_mode();
   void set_to_game_play_mode();
};



