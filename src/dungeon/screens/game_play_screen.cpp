


#include <dungeon/screens/game_play_screen.hpp>

//#include <framework/screens/gamer_input_screen.hpp>
#include <dungeon/models/entities/door_entity.hpp>
#include <dungeon/entity_controllers/ai_controller_base.hpp>
#include <dungeon/entity_controllers/ai_kid_controller.hpp>
#include <dungeon/entity_controllers/ai_knight_controller.hpp>
#include <dungeon/emitters/user_event_emitter.hpp>
#include <dungeon/factories/entity_factory.hpp>
#include <dungeon/factories/scene_factory.hpp>
#include <dungeon/helpers/scene_collection_helper.hpp>
#include <dungeon/item_type_nums.hpp>
#include <dungeon/motion_fx_type_names.hpp>
#include <dungeon/music_track_nums.hpp>
#include <dungeon/user_events.hpp>
#include <AllegroFlare/EventNames.hpp>


#define TEST_SCENE_ID 999
#define START_SCENE_ID 0



//GamePlayScreen::GamePlayScreen(GamerInputScreen *gamer_input_screen)
GamePlayScreen::GamePlayScreen(AllegroFlare::EventEmitter *event_emitter, AllegroFlare::BitmapBin *bitmap_bin, AllegroFlare::FontBin *font_bin)
   : AllegroFlare::Screens::Base()
   , scene(nullptr)
   , state(NONE)
   , player_krampus_controller()
   , ai_controllers()
   , player_inventory()
   , naughty_list()
   , event_emitter(event_emitter)
   , bitmap_bin(bitmap_bin)
   , font_bin(font_bin)
   , hud(font_bin, bitmap_bin->auto_get("sprites_grid-x.png"), &player_inventory, &naughty_list)
   , inventory_screen(font_bin, &player_inventory)
   , state_helper(event_emitter, this)
   , camera(nullptr)
   , _item_recently_collected(0)
   //, gamer_input_screen(gamer_input_screen)
{
   if (!event_emitter) throw std::runtime_error("GamePlayScreen:: no event_emitter");
   enter_scene(START_SCENE_ID);
   set_state(GAME_PLAY);
}



void GamePlayScreen::primary_timer_func()
{
   //update(gamer_input_screen);
   draw();
}



void GamePlayScreen::user_event_func(ALLEGRO_EVENT *ev)
{
   ALLEGRO_EVENT *event = ev;

   switch (event->user.type)
   {
      case PLAYER_DIED_EVENT:
      {
         set_state(GAME_LOST);
      }
      //case ALLEGRO_EVENT_GAMER_BUTTON_DOWN:
      case ALLEGRO_FLARE_EVENT_VIRTUAL_CONTROL_BUTTON_DOWN:
      {
         int user_input = event->user.data1;
         state_helper.process_key_down(user_input);
         break;
      }
      //case ALLEGRO_EVENT_GAMER_BUTTON_UP:
      case ALLEGRO_FLARE_EVENT_VIRTUAL_CONTROL_BUTTON_UP:
      {
         switch (state)
         {
            case GAME_PLAY:
            {
               int user_input = event->user.data1;
               player_krampus_controller.on_key_up(user_input);
               break;
            }
            default: break;
         }
         break;
      }
      case ENTER_DOOR_EVENT:
      {
         int scene_id = event->user.data1;
         std::string destination_door_name;
         destination_door_name.push_back((char)event->user.data2);
         enter_scene(scene_id, destination_door_name[0]);
         break;
      }
      case SPAWN_MOTION_FX:
      {
         std::string *type = (std::string *)event->user.data1;

         if (*type == MOTION_FX_DAMAGE_HIT)
         {
            int x = event->user.data2;
            int y = event->user.data3;
            std::string *damage_string = (std::string *)event->user.data4;
            EntityFactory::create_hit_damage_motion_fx(scene, x, y, *damage_string);
            delete damage_string;
         }
         if (*type == MOTION_FX_REVERSE_EXPLOSION)
         {
            int x = event->user.data2;
            int y = event->user.data3;
            EntityFactory::create_reverse_explosion_fx(scene, x, y);
         }
         if (*type == MOTION_FX_SLASH_POOF)
         {
            int x = event->user.data2;
            int y = event->user.data3;
            EntityFactory::create_slash_poof_fx(scene, x, y);
            std::cout << "slash poof created" << std::endl;
         }

         delete type;
         break;
      }
      case COLLECT_ITEM_EVENT:
      {
         int item_type_int = event->user.data1;
         player_inventory.add_item(item_type_int);
         _item_recently_collected = item_type_int;

         if (item_type_int == ITEM_TYPE_CLUB)
         {
            SceneCollectionHelper collections(scene);
            KrampusEntity *krampus = collections.get_krampus();
            krampus->get_weapon();
            event_emitter->emit_event(PLAY_SOUND_EFFECT, 0, (intptr_t)(new std::string(SWORD_SCHLING_SOUND_EFFECT)));
         }
         else if (item_type_int == ITEM_TYPE_STONE_OF_DEFIANCE)
         {
            SceneCollectionHelper collections(scene);
            KrampusEntity *krampus = collections.get_krampus();
            krampus->get_stone_of_defiance();
         }

         set_state(ITEM_COLLECTED);
         break;
      }
      case USE_STONE_OF_DEFIANCE_EVENT:
      {
         set_state(USING_STONE_OF_DEFIANCE);
         break;
      }
      case OPEN_INVENTORY_SCREEN:
      {
         inventory_screen.show();
         set_state(INVENTORY_SCREEN);
         break;
      }
      case CLOSE_INVENTORY_SCREEN:
      {
         inventory_screen.hide();
         set_state(GAME_PLAY);
         break;
      }
      case INVENTORY_SCREEN__MOVE_CURSOR_UP:
         inventory_screen.move_cursor_up();
         break;
      case INVENTORY_SCREEN__MOVE_CURSOR_DOWN:
         inventory_screen.move_cursor_down();
         break;
      case INVENTORY_SCREEN__MOVE_CURSOR_LEFT:
         inventory_screen.move_cursor_left();
         break;
      case INVENTORY_SCREEN__MOVE_CURSOR_RIGHT:
         inventory_screen.move_cursor_right();
         break;
      case INVENTORY_SCREEN__SELECT_ITEM:
         inventory_screen.select_item_at_cursor();
         break;
      case INVENTORY_EQUIP_WEAPON:
      {
         int item_type_int = event->user.data1;
         player_inventory.set_equipped_weapon(item_type_int);
         break;
      }
      case INVENTORY_EQUIP_SHIELD:
      {
         int item_type_int = event->user.data1;
         player_inventory.set_equipped_shield(item_type_int);
         break;
      }
      case INVENTORY_EQUIP_ITEM:
      {
         int item_type_int = event->user.data1;
         player_inventory.set_equipped_item(item_type_int);
         break;
      }
   }
}



void GamePlayScreen::update(GamerInputScreen *gamer_input_screen)
{
   state_helper.update_state(gamer_input_screen);
}



void GamePlayScreen::draw()
{
   state_helper.draw_state();
}



void GamePlayScreen::set_state(state_t new_state)
{
   state_helper.set_state(new_state);
}



void GamePlayScreen::enter_scene(int scene_id, char door_name)
{
   if (scene) delete scene;

   scene = SceneFactory::create_scene_by_id(scene_id);

   SceneCollectionHelper collections(scene);

   std::vector<NaughtyList::Kid> naughty_list_kids = naughty_list.get_alive_kids_for_scene(scene_id);
   KrampusEntity *krampus = collections.get_krampus();
   DoorEntity *door = collections.get_door(door_name);

   // create entities for the alive kids in this scene
   for (auto &kid : naughty_list_kids)
   {
      float min_y, max_y;
      float scene_width = scene->get_width();
      scene->get_y_bounds(&min_y, &max_y);

      float new_kid_x = random.get_random_float(0, scene->get_width());
      float new_kid_y = random.get_random_float(min_y, max_y);

      EntityFactory::create_named_kid(scene, kid.get_name(), kid.get_behavior(), kid.get_sprite_index(), new_kid_x, new_kid_y);
   }

   // create a knight because you can
   float min_y, max_y;
   float scene_width = scene->get_width();
   scene->get_y_bounds(&min_y, &max_y);
   float new_knight_x = random.get_random_float(0, scene->get_width());
   float new_knight_y = random.get_random_float(min_y, max_y);
   EntityFactory::create_knight_entity(scene, new_knight_x, new_knight_y);

   EntityFactory::create_skull_enemy(scene, scene_width, new_knight_y, min_y, max_y);

   // create AI controllers to control all the enemies
   for (auto &ai_controller : ai_controllers)
      delete ai_controller;

   ai_controllers.clear();

   for (auto &kid : collections.get_kids())
      ai_controllers.push_back(new AIKidController(kid));

   for (auto &knight : collections.get_knights())
      ai_controllers.push_back(new AIKnightController(knight));

   // equip the KrampusEntity with a weapon (if the player has one)
   if (player_inventory.has_item(ITEM_TYPE_CLUB)) krampus->get_weapon();
   if (player_inventory.has_item(ITEM_TYPE_STONE_OF_DEFIANCE)) krampus->get_stone_of_defiance();

   // set the player controller to control krampus
   player_krampus_controller.set_krampus(krampus);

   // have the camera follow krampus
   camera.set_target(krampus);

   // start (or resume) the music for this scene
   event_emitter->emit_event(PLAY_MUSIC_TRACK, HAUNTING_MUSIC);

   // place krampus at the destination_door and walk down
   if (door)
   {
      krampus->place.position = door->place.position + AllegroFlare::Vec2D{ 0.0, door->place.h/2 + krampus->place.h/2 } + 5;
   }

   set_state(ENTERING_THROUGH_DOOR);
}



void GamePlayScreen::_destroy_ai_controller(Entity::Base *entity)
{
   for (unsigned i=0; i<ai_controllers.size(); i++)
      if (ai_controllers[i]->is_controlling(entity))
      {
         delete ai_controllers[i];
         ai_controllers.erase(ai_controllers.begin() + i);
         i--;
      }
}



