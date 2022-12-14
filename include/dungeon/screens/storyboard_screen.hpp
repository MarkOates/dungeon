#pragma once


#include <allegro5/allegro_font.h>
//#include <framework/screen.hpp>
#include <AllegroFlare/Displays/Screen.hpp>



class StoryboardScreen : public AllegroFlare::Displays::Screen
{
private:
   ALLEGRO_FONT *text_font;
   int current_page;
   std::vector<std::string> pages;
   intptr_t event_to_emit_after_completing;

public:
	StoryboardScreen(std::vector<std::string> pages, intptr_t event_to_emit_after_completing);

   void primary_timer_func() override;
   void user_event_func() override;
};


