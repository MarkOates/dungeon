#pragma once


#include <allegro5/allegro_font.h>
//#include <framework/screen.hpp>
#include <AllegroFlare/Screens/Base.hpp>
#include <AllegroFlare/EventEmitter.hpp>



class StoryboardScreen : public AllegroFlare::Screens::Base
{
private:
   AllegroFlare::EventEmitter *event_emitter;
   ALLEGRO_FONT *text_font;
   int current_page;
   std::vector<std::string> pages;
   intptr_t event_to_emit_after_completing;

public:
	StoryboardScreen(AllegroFlare::EventEmitter *event_emitter, std::vector<std::string> pages, ALLEGRO_FONT *_font, intptr_t event_to_emit_after_completing);

   void primary_timer_func() override;
   void user_event_func(ALLEGRO_EVENT *ev) override;
};


