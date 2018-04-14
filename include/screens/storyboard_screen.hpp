#pragma once


#include <allegro5/allegro_font.h>
#include <framework/screen.hpp>


class StoryboardScreen : public Screen
{
private:
   ALLEGRO_FONT *text_font;
   int current_page;
   std::vector<std::string> pages;
   intptr_t event_to_emit_after_completing;

public:
	StoryboardScreen(Display *display, std::vector<std::string> pages, intptr_t event_to_emit_after_completing);

   void primary_timer_func() override;
   void user_event_func() override;
};


