#pragma once


class GamePlayScreen;
class GamerInputScreen;
namespace AllegroFlare { class EventEmitter; class Random; };
#include <AllegroFlare/Random.hpp>


class GamePlayScreenStateHelper
{
private:
   AllegroFlare::EventEmitter *event_emitter;
   GamePlayScreen *game_play_screen;
   AllegroFlare::Random random;
   float state_counter;
   bool _can_bypass_dialogue();

public:
   GamePlayScreenStateHelper(AllegroFlare::EventEmitter *event_emitter, GamePlayScreen *game_play_screen);

   void process_key_down(int input_button);
   void set_state(int new_state);
   void update_state(GamerInputScreen *gamer_input_screen);
   void draw_state();

   void update_scene();
   void draw_scene_with_camera();

   void check_for_win_or_loss_condition();
};


