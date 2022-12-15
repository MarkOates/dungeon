#pragma once


#include <dungeon/screens/storyboard_screen.hpp>


class StoryboardFactory
{
public:
   static StoryboardScreen *create_opening_storyboard_screen(AllegroFlare::EventEmitter *event_emitter, ALLEGRO_FONT *font);
   static StoryboardScreen *create_closing_storyboard_screen(AllegroFlare::EventEmitter *event_emitter, ALLEGRO_FONT *font);
};


