


#include <dungeon/models/hud.hpp>

//#include <framework/framework.hpp>
//#include <framework/image_processing.hpp>
//#include <framework/objects/text_object.hpp>
#include <dungeon/models/text_object.hpp>
#include <dungeon/item_type_nums.hpp>
#include <sstream>

#include <allegro5/allegro_primitives.h>
#include <AllegroFlare/ImageProcessing.hpp>
#include <AllegroFlare/Color.hpp>



HUD::HUD(AllegroFlare::FontBin *font_bin, ALLEGRO_BITMAP *sprites_grid, Inventory *player_inventory, NaughtyList *naughty_list)
   : player_inventory(player_inventory)
   , naughty_list(naughty_list)
   , player_health(0)
   , player_max_health(0)
   , chrome_bitmap(nullptr)
   , font(nullptr)
   , font_bigger(nullptr)
   , black_bar_counter(0)
   , sprite_sheet(sprites_grid, SPRITES_GRID_SPRITE_WIDTH, SPRITES_GRID_SPRITE_HEIGHT, SPRITES_GRID_SPRITE_SCALING)
   , weapon_bitmap(nullptr)
   , shield_bitmap(nullptr)
   , item_bitmap(nullptr)
{
   if (!font_bin) throw std::runtime_error("HUD:: no font_bin!");
   if (!sprites_grid) throw std::runtime_error("HUD:: no sprites_grid!");

   font = font_bin->auto_get("ChronoTrigger.ttf 40");
   font_bigger = font_bin->auto_get("ChronoTrigger.ttf 55");


   AllegroFlare::ImageProcessing image_processing(sprites_grid);
   ALLEGRO_BITMAP *bmp = image_processing.create_pixel_perfect_scaled_render( 5);
   chrome_bitmap.bitmap(bmp);

   chrome_bitmap.position(1920/2, 20);
   chrome_bitmap.align(0.5, 2.0);
   chrome_bitmap.scale(0.95);

   weapon_bitmap.bitmap(sprite_sheet.get_sprite(31))
      .position(640-135, 84)
      .scale(0.6)
      .align(0.5, 0.5)
      .rotation(0.1);

   shield_bitmap.bitmap(sprite_sheet.get_sprite(28))
      .position(640-40, 84)
      .scale(0.6)
      .align(0.5, 0.5)
      .rotation(0.1);

   item_bitmap.bitmap(sprite_sheet.get_sprite(24))
      .position(435*2-130, 48*2-18)
      .scale(1.0)
      .align(0.5, 0.5)
      .rotation(0.1);

   set_to_game_play_mode();
}



void HUD::set_mode(mode_t new_mode)
{
   mode = new_mode;

   switch(new_mode)
   {
   case MODE_GAME_PLAY:
      chrome_bitmap.get_attr("align_y") = 0.0; //<- a really annoying way to have to do this
      weapon_bitmap.scale(1.6, 1.6);
      shield_bitmap.scale(1.6, 1.6);
      item_bitmap.scale(1.65, 1.65);
      black_bar_counter = 0.0;
      break;
   case MODE_CINEMA:
      chrome_bitmap.get_attr("align_y") = 2.0; //<- a really annoying way to have to do this
      weapon_bitmap.scale(0.0, 0.0);
      shield_bitmap.scale(0.0, 0.0);
      item_bitmap.scale(0.0, 0.0);
      black_bar_counter = 1.0;
      break;
   default:
      break;
   };
}



void HUD::set_values(int player_health, int player_max_health)
{
   this->player_health = player_health;
   this->player_max_health = player_max_health;
}



void HUD::set_weapon(ALLEGRO_BITMAP *bmp)
{
   weapon_bitmap.bitmap(bmp);
}



void HUD::set_shield(ALLEGRO_BITMAP *bmp)
{
   shield_bitmap.bitmap(bmp);
}



void HUD::set_item(ALLEGRO_BITMAP *bmp)
{
   item_bitmap.bitmap(bmp);
}



void HUD::draw()
{
   chrome_bitmap.draw();

   weapon_bitmap.draw();
   shield_bitmap.draw();
   item_bitmap.draw();

   // fill the player health bar
   std::string player_health_str = "";
   // NOTE: std::to_string here to replace previous tostring
   player_health_str += std::to_string(player_health) + " / " + std::to_string(player_max_health);
   if (mode == MODE_GAME_PLAY) al_draw_text(font, AllegroFlare::color::white, 324, 86, ALLEGRO_ALIGN_CENTRE, player_health_str.c_str());

   // draw the black bars
   float black_bar_height = 100;
   float top_bar_y = 0 - black_bar_height * (1.0 - black_bar_counter);
   float bottom_bar_y = 1080-black_bar_height + black_bar_height * (1.0 - black_bar_counter);
   //al_draw_filled_rectangle(0, top_bar_y, 1920, top_bar_y+black_bar_height, AllegroFlare::color::black);
   //al_draw_filled_rectangle(0, bottom_bar_y, 1920, bottom_bar_y+black_bar_height, AllegroFlare::color::black);
}



void HUD::set_to_cinema_mode()
{
   set_mode(MODE_CINEMA);
}



void HUD::set_to_game_play_mode()
{
   set_mode(MODE_GAME_PLAY);
}


