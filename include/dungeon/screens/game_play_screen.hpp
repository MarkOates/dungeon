#pragma once


#include <dungeon/entity_controllers/player_krampus_controller.hpp>
//#include <dungeon/helpers/game_play_screen_state_helper.hpp>
#include <dungeon/models/camera.hpp>
#include <dungeon/models/hud.hpp>
#include <dungeon/models/inventory.hpp>
#include <dungeon/models/inventory_screen.hpp>
#include <dungeon/models/naughty_list.hpp>
#include <dungeon/models/scene.hpp>
#include <AllegroFlare/Screens/Base.hpp>
#include <AllegroFlare/BitmapBin.hpp>
#include <AllegroFlare/FontBin.hpp>
#include <AllegroFlare/EventEmitter.hpp>
#include <AllegroFlare/Shader.hpp>
//#include <framework/screen.hpp>


class AIControllerBase;


class GamePlayScreen : public AllegroFlare::Screens::Base
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
   AllegroFlare::EventEmitter *event_emitter;
   AllegroFlare::BitmapBin *bitmap_bin;
   AllegroFlare::FontBin *font_bin;
   AllegroFlare::Random random;
   AllegroFlare::Shader flat_color_shader;
   state_t state;
   Scene *scene;
   PlayerKrampusController player_krampus_controller;
   std::vector<AIControllerBase *> ai_controllers;
   Inventory player_inventory;
   NaughtyList naughty_list;
   HUD hud;
   InventoryScreen inventory_screen;
   //GamePlayScreenStateHelper state_helper;
   Camera camera;
   //AllegroFlare::EventEmitter *event_emitter;
   //GamePlayScreen *game_play_screen;
   //AllegroFlare::Random random;
   float state_counter;
   //bool _can_bypass_dialogue();
   bool up_pressed;
   bool down_pressed;
   bool left_pressed;
   bool right_pressed;
   bool initialized;

   //GamerInputScreen *gamer_input_screen;

   //friend class GamePlayScreenStateHelper;

   int _item_recently_collected;
   void _destroy_ai_controller(Entity::Base *entity);

public:
   GamePlayScreen(AllegroFlare::EventEmitter *event_emitter, AllegroFlare::BitmapBin *bitmap_bin, AllegroFlare::FontBin *font_bin);

   void init();

   virtual void primary_timer_func() override;
   virtual void user_event_func(ALLEGRO_EVENT *ev) override;
   virtual void virtual_control_button_up_func(int player_num, int button_num, bool repeat=false) override;
   virtual void virtual_control_button_down_func(int player_num, int button_num, bool repeat=false) override;
   virtual void virtual_control_axis_change_func(ALLEGRO_EVENT *ev) override;
   virtual void key_down_func(ALLEGRO_EVENT *ev) override;


   void update();
   void draw();

   void update_scene();
   void draw_scene_with_camera();
   void check_for_win_or_loss_condition();
   bool _can_bypass_dialogue();
   void set_state(state_t new_state);
   void enter_scene(int scene_to_enter, char door_name='!');
   AllegroFlare::Shader *get_flat_color_shader();
};


