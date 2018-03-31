


#include <framework/screens/gamer_input_screen.hpp>
#include <framework/framework.hpp>
#include <screens/title_screen.hpp>
#include <emitters/user_event_emitter.hpp>
#include <item_type_nums.hpp>
#include <user_events.hpp>



#define MENU_OPTION_QUICK_START "quick start"
#define MENU_OPTION_START "start"
#define MENU_OPTION_EXIT "exit"



TitleScreen::TitleScreen(Display *display)
   : Screen(display)
   , sprite_sheet(SPRITES_GRID_FILENAME, SPRITES_GRID_SPRITE_WIDTH, SPRITES_GRID_SPRITE_HEIGHT, SPRITES_GRID_SPRITE_SCALING)
   , fonts()
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
   ALLEGRO_FONT *font = fonts["ChronoTrigger.ttf 60"];

   title.font(font)
      .align(0.5, 1.0)
      .scale(2.5, 2.5)
      .color(color::mix(color::yellow, color::red, 0.6))
      .position(display->center(), display->middle()-100);

   title2.font(font)
      .align(0.5, -0.1)
      .scale(1.5, 1.5)
      .color(color::mix(color::yellow, color::red, 0.9))
      .position(display->center(), display->middle()-100);

   menu_cursor_sprite
      .align(0.5, 0.5)
      .anchor(0, 20)
      .rotation(FULL_ROTATION * 0.25);

   int count = 0;
   for (auto &menu_item : menu_items)
   {
      menu_item.first.font(font)
         .align(0, 0.5)
         .scale(1.0, 1.0)
         .position(display->center(), display->middle()+count*50 + 100);

      count++;
   }

   refresh_focused_menu_item();
}



void TitleScreen::primary_timer_func()
{
   al_clear_to_color(color::black);

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
         float height = menu_item.first._placement->h;
         menu_cursor_sprite.position(-30, height/2);
         menu_cursor_sprite.draw();
         menu_item.first._placement->restore_transform();
      }
      menu_item.first.draw();
      i++;
   }
}



void TitleScreen::user_event_func()
{
   ALLEGRO_USER_EVENT &user_event = Framework::current_event->user;
   switch(user_event.type)
   {
   case ALLEGRO_EVENT_GAMER_BUTTON_DOWN:
      {
         int input_button = user_event.data1;
         std::cout << "TitleScreen::user_event_func() button " << user_event.data1 << std::endl;
         switch (input_button)
         {
         case GAMER_BUTTON_UP:
            cursor_up_action();
            break;
         case GAMER_BUTTON_DOWN:
            cursor_down_action();
            break;
         case GAMER_BUTTON_START:
         case GAMER_BUTTON_A:
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
      if (i == menu_cursor_pos) menu_items[i].first.scale(1.5, 1.5).color(color::white);
      else menu_items[i].first.scale(1.0, 1.0).color(color::gray);
   }
}



void TitleScreen::select_option_action()
{
   state = ITEM_SELECTED;

   std::pair<TextObject, int32_t> &menu_item = menu_items[menu_cursor_pos];
   std::cout << "TitleScreen: emitting event \"" << menu_item.first.str << "\"\n";

   UserEventEmitter::emit_event(menu_item.second);
}



