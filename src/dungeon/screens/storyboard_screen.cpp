


#include <dungeon/screens/storyboard_screen.hpp>

//#include <framework/screens/gamer_input_screen.hpp>
#include <dungeon/emitters/user_event_emitter.hpp>
//#include <framework/framework.hpp>
#include <dungeon/user_events.hpp>
#include <AllegroFlare/Color.hpp>
#include <AllegroFlare/EventNames.hpp>


StoryboardScreen::StoryboardScreen(AllegroFlare::EventEmitter *event_emitter, std::vector<std::string> pages, ALLEGRO_FONT *_font, intptr_t event_to_emit_after_completing)
   : AllegroFlare::Screens::Base()
   , event_emitter(event_emitter)
   , text_font(_font)
   , pages(pages)
   , current_page(0)
   , event_to_emit_after_completing(event_to_emit_after_completing)
{
   if (!event_emitter) throw std::runtime_error("StoryboardScreen:: no event emitter");
}



void StoryboardScreen::primary_timer_func()
{
   al_clear_to_color(AllegroFlare::color::hex("11141a"));

   if (current_page >= pages.size()) return;

   float x_padding = 150;
   float y_padding = 150;

   al_draw_multiline_text(
         text_font,
         AllegroFlare::color::hex("d0f2c5"),
         x_padding,
         y_padding,
         //display->width() - x_padding*2,
         1920 - x_padding*2,
         al_get_font_line_height(text_font)*1.75,
         0,
         pages[current_page].c_str()
      );
}



void StoryboardScreen::user_event_func(ALLEGRO_EVENT *ev)
{
   //ALLEGRO_USER_EVENT &user_event = Framework::current_event->user;
   ALLEGRO_USER_EVENT &user_event = ev->user;
   switch(user_event.type)
   {
      // NOTE: this changed::
   case ALLEGRO_FLARE_EVENT_VIRTUAL_CONTROL_BUTTON_DOWN:
      //ALLEGRO_EVENT_GAMER_BUTTON_DOWN:
      {
         std::cout << "StoryboardScreen::user_event_func() button " << user_event.data1 << std::endl;
         int input_button = user_event.data1;
         switch (input_button)
         {
         default:
         // NOTE: this changed
         //case GAMER_BUTTON_RIGHT:
         //case GAMER_BUTTON_A:
         //case GAMER_BUTTON_B:
         //case GAMER_BUTTON_C:
            current_page++;
            break;
         }
      }
      break;
   }

   //if (current_page >= pages.size())
      //UserEventEmitter::emit_event(event_to_emit_after_completing);
   if (current_page >= pages.size())
      event_emitter->emit_event(event_to_emit_after_completing);
}



