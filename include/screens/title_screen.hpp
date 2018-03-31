#pragma once



#include <framework/screen.hpp>
#include <framework/objects/text_object.hpp>
#include <framework/objects/bitmap_object.hpp>
#include <models/sprite_sheet.hpp>



class TitleScreen : public Screen
{
private:
   enum
   {
      SHOWING_TITLE,
      ITEM_SELECTED
   };

public:
   SpriteSheet sprite_sheet;
   FontBin fonts;
   int menu_cursor_pos;
   TextObject title;
   TextObject title2;
   std::vector<std::pair<TextObject, int32_t>> menu_items;
   int state;
   BitmapObject menu_cursor_sprite;

   TitleScreen(Display *display);

   void primary_timer_func() override;
   void user_event_func() override;

   void cursor_up_action();
   void cursor_down_action();
   void select_option_action();

   void refresh_focused_menu_item();
};



