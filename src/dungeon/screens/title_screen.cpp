


#include <dungeon/screens/title_screen.hpp>

//#include <framework/screens/gamer_input_screen.hpp>
//#include <framework/framework.hpp>
#include <dungeon/emitters/user_event_emitter.hpp>
#include <dungeon/item_type_nums.hpp>
#include <dungeon/user_events.hpp>
#include <AllegroFlare/Color.hpp>
#include <AllegroFlare/EventNames.hpp>
#include <AllegroFlare/VirtualControls.hpp>


#include <AllegroFlare/Useful.hpp> // for FULL_ROTATION


#define MENU_OPTION_QUICK_START "quick start"
#define MENU_OPTION_START "start"
#define MENU_OPTION_EXIT "exit"



TitleScreen::TitleScreen(AllegroFlare::EventEmitter *event_emitter, AllegroFlare::FontBin *font_bin, ALLEGRO_BITMAP *sprites_grid_bitmap)
//TitleScreen::TitleScreen(ALLEGRO_BITMAP *sprites_grid_bitmap)
   : AllegroFlare::Screens::Base()
   , sprite_sheet(sprites_grid_bitmap, SPRITES_GRID_SPRITE_WIDTH, SPRITES_GRID_SPRITE_HEIGHT, SPRITES_GRID_SPRITE_SCALING)
   , font_bin(font_bin)
   , event_emitter(event_emitter)
   , menu_cursor_pos(0)
   , title(TextObject("KRAMPUS RETURNS"))
   , title2(TextObject("THE UPRISING"))
   , menu_items({
         { TextObject(MENU_OPTION_QUICK_START), START_GAME_EVENT },
         { TextObject(MENU_OPTION_START), START_INTRO_STORYBOARD_SCREEN },
         { TextObject(MENU_OPTION_EXIT), QUIT_GAME_EVENT }
      })
   , state(SHOWING_TITLE)
   , menu_cursor_sprite(BitmapObject(sprite_sheet.get_sprite(33)))
{
   if (!font_bin) throw std::runtime_error("TitleScreen no font bin");
   if (!event_emitter) throw std::runtime_error("TitleScreen no event_emitter");
   ALLEGRO_FONT *font = font_bin->auto_get("ChronoTrigger.ttf 60");

   title.font(font)
      .align(0.5, 1.0)
      .scale(2.5, 2.5)
      //.color(color::mix(color::yellow, color::red, 0.6))
      .position(1920/2, 1080/2-100);
      //.position(display->center(), display->middle()-100);

   title2.font(font)
      .align(0.5, -0.1)
      .scale(1.5, 1.5)
      //.color(color::mix(color::yellow, color::red, 0.9))
      .position(1920/2, 1080/2-100);
      //.position(display->center(), display->middle()-100);

   menu_cursor_sprite
      .align(0.5, 0.5)
      .anchor(0, 20)
      .rotation(AllegroFlare::FULL_ROTATION * 0.25);

   int count = 0;
   for (auto &menu_item : menu_items)
   {
      menu_item.first.font(font)
         .align(0, 0.5)
         .scale(1.0, 1.0)
         .position(1920/2, 1080/2+count*50 + 100);
         //.position(display->center(), display->middle()+count*50 + 100);

      count++;
   }

   refresh_focused_menu_item();
}



void TitleScreen::primary_timer_func()
{
   al_clear_to_color(AllegroFlare::color::black);

   // draw the title
   title.draw();
   title2.draw();

   // draw the menu options
   int i = 0;
   for (auto &menu_item : menu_items)
   {
      if (i == menu_cursor_pos)
      {
         menu_item.first._placement->start_transform();
         float height = menu_item.first._placement->size.y;
         menu_cursor_sprite.position(-30, height/2);
         menu_cursor_sprite.draw();
         menu_item.first._placement->restore_transform();
      }
      menu_item.first.draw();
      i++;
   }
}



//#include <AllegroFlare/EventNames.hpp>
   //case ALLEGRO_FLARE_EVENT_VIRTUAL_CONTROL_BUTTON_DOWN:


void TitleScreen::user_event_func(ALLEGRO_EVENT *ev)
{
   auto &BUTTON_UP = AllegroFlare::VirtualControls::BUTTON_UP;
   auto &BUTTON_DOWN = AllegroFlare::VirtualControls::BUTTON_DOWN;
   auto &BUTTON_START = AllegroFlare::VirtualControls::BUTTON_START;
   auto &BUTTON_A = AllegroFlare::VirtualControls::BUTTON_A;

   ALLEGRO_USER_EVENT &user_event = ev->user;
   //ALLEGRO_USER_EVENT &user_event = Framework::current_event->user;
   switch(user_event.type)
   {
   case ALLEGRO_FLARE_EVENT_VIRTUAL_CONTROL_BUTTON_DOWN:
   //case ALLEGRO_EVENT_GAMER_BUTTON_DOWN:
      {
         int input_button = user_event.data1;
         std::cout << "TitleScreen::user_event_func() button " << user_event.data1 << std::endl;
         switch (input_button)
         {
         case BUTTON_UP:
            cursor_up_action();
            break;
         case BUTTON_DOWN:
            cursor_down_action();
            break;
         case BUTTON_START:
         case BUTTON_A:
            select_option_action();
            break;
         }
      }
      break;
   }
}



void TitleScreen::cursor_up_action()
{
   menu_cursor_pos--;
   if (menu_cursor_pos < 0) menu_cursor_pos = menu_items.size() - 1;
   refresh_focused_menu_item();
}



void TitleScreen::cursor_down_action()
{
   menu_cursor_pos++;
   if (menu_cursor_pos >= menu_items.size()) menu_cursor_pos = 0;
   refresh_focused_menu_item();
}



void TitleScreen::refresh_focused_menu_item()
{
   for (unsigned i=0; i<menu_items.size(); i++)
   {
      if (i == menu_cursor_pos) menu_items[i].first.scale(1.5, 1.5); //.color(AllegroFlare::color::white);
      else menu_items[i].first.scale(1.0, 1.0); //.color(AllegroFlare::color::gray);
   }
}



void TitleScreen::select_option_action()
{
   state = ITEM_SELECTED;

   std::pair<TextObject, int32_t> &menu_item = menu_items[menu_cursor_pos];
   std::cout << "TitleScreen: emitting event \"" << menu_item.first.str << "\"\n";

   //UserEventEmitter::emit_event(menu_item.second);
   event_emitter->emit_event(menu_item.second);
}



