#pragma once



#include <framework/screen.hpp>

#include <controllers/player_krampus_controller.hpp>
#include <helpers/game_play_screen_state_helper.hpp>
#include <models/camera.hpp>
#include <models/hud.hpp>
#include <models/inventory.hpp>
#include <models/inventory_screen.hpp>
#include <models/naughty_list.hpp>
#include <models/scene.hpp>



class AIControllerBase;



class GamePlayScreen : public Screen
{
private:
   enum state_t
   {
      NONE,
      GET_READY,
      GAME_PLAY,
      GAME_LOST,
      GAME_WON,
      PLAYER_DIED,
      PAUSED,
      ITEM_COLLECTED,
      INVENTORY_SCREEN,
      USING_STONE_OF_DEFIANCE,
      ENTERING_THROUGH_DOOR,
      BOSS_FIGHT_WARM_UP,
      BOSS_FIGHT,
      STATE_COMPLETE
   };
   state_t state;
   Scene *scene;
   PlayerKrampusController player_krampus_controller;
   std::vector<AIControllerBase *> ai_controllers;
   Inventory player_inventory;
   NaughtyList naughty_list;
   HUD hud;
   InventoryScreen inventory_screen;
   GamePlayScreenStateHelper state_helper;
   Camera camera;
   GamerInputScreen *gamer_input_screen;

   friend class GamePlayScreenStateHelper;

   int _item_recently_collected;
   void _destroy_ai_controller(EntityBase *entity);

public:
   GamePlayScreen(Display *display, GamerInputScreen *gamer_input_screen);

   void primary_timer_func() override;
   void user_event_func() override;

   void update(GamerInputScreen *gamer_input_screen);
   void draw();

   void set_state(state_t new_state);
   void enter_scene(int scene_to_enter, char door_name='!');
};



