#pragma once


//#include <framework/screen.hpp>
//#include <framework/objects/text_object.hpp>
//#include <framework/objects/bitmap_object.hpp>
#include <dungeon/models/sprite_sheet.hpp>
#include <AllegroFlare/Screens/Base.hpp>
#include <AllegroFlare/FontBin.hpp>
#include <AllegroFlare/EventEmitter.hpp>
#include <dungeon/models/text_object.hpp>
#include <dungeon/models/bitmap_object.hpp>


class TitleScreen : public AllegroFlare::Screens::Base
{
private:
   enum
   {
      SHOWING_TITLE,
      ITEM_SELECTED
   };

public:
   SpriteSheet sprite_sheet;
   AllegroFlare::FontBin *font_bin;
   AllegroFlare::EventEmitter *event_emitter;
   int menu_cursor_pos;
   TextObject title;
   TextObject title2;
   std::vector<std::pair<TextObject, int32_t>> menu_items;
   int state;
   BitmapObject menu_cursor_sprite;

   TitleScreen(AllegroFlare::EventEmitter *event_emitter, AllegroFlare::FontBin *font_bin, ALLEGRO_BITMAP *sprites_grid_bitmap);

   void primary_timer_func() override;
   void user_event_func(ALLEGRO_EVENT *ev) override;

   void cursor_up_action();
   void cursor_down_action();
   void select_option_action();

   void refresh_focused_menu_item();
};


