


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
#include <AllegroFlare/VirtualControls.hpp>


#include <dungeon/models/entities/enemy/base.hpp>
//#include <framework/screens/gamer_input_screen.hpp>
#include <dungeon/entity_controllers/ai_controller_base.hpp>
#include <dungeon/emitters/user_event_emitter.hpp>
#include <dungeon/factories/dialogue_factory.hpp>
#include <dungeon/helpers/scene_collection_helper.hpp>
#include <dungeon/screens/game_play_screen.hpp>
#include <dungeon/item_type_nums.hpp>
#include <dungeon/music_track_nums.hpp>
#include <dungeon/user_events.hpp>

#include <AllegroFlare/EventEmitter.hpp>
#include <AllegroFlare/VirtualControls.hpp>
#include <AllegroFlare/Color.hpp>
#include <AllegroFlare/Random.hpp>

#include <AllegroFlare/InteractiveDevelopment.hpp>
#include <AllegroFlare/UsefulPHP.hpp>




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
   , flat_color_shader(
         AllegroFlare::php::file_get_contents("data/shaders/flat_color_shader.vertex.glsl"),
         AllegroFlare::php::file_get_contents("data/shaders/flat_color_shader.fragment.glsl")
      )
   //, flat_color_shader("data/shaders/flat_color_shader.vertex.glsl", "data/shaders/flat_color_shader.fragment.glsl")
   , naughty_list()
   , event_emitter(event_emitter)
   , bitmap_bin(bitmap_bin)
   , font_bin(font_bin)
   , hud(&flat_color_shader, bitmap_bin, font_bin, bitmap_bin->auto_get("top_hud-x.png"), &player_inventory, &naughty_list)
   , inventory_screen(font_bin, &player_inventory)
   //, state_helper(event_emitter, this)
   , camera(nullptr)
   , _item_recently_collected(0)
   //, gamer_input_screen(gamer_input_screen)


   //: event_emitter(event_emitter)
   //, game_play_screen(game_play_screen)
   , random()
   , state_counter(1.0)
   , up_pressed(false)
   , down_pressed(false)
   , left_pressed(false)
   , right_pressed(false)
   , initialized(false)
{
   if (!event_emitter) throw std::runtime_error("GamePlayScreen:: no event_emitter");
}



void GamePlayScreen::init()
{
   flat_color_shader.initialize();
   enter_scene(START_SCENE_ID);
   set_state(GAME_PLAY);
   initialized = true;
}



void GamePlayScreen::primary_timer_func()
{
   update();
   draw();
}




void GamePlayScreen::virtual_control_button_up_func(int player_num, int button_num, bool repeat)
{
   switch (state)
   {
      case GAME_PLAY:
      {
         //int user_input = event->user.data1;
         player_krampus_controller.on_key_up(button_num);
         break;
      }
      default: break;
   }
   //player_krampus_controller.on_key_up(user_input);
}




void GamePlayScreen::virtual_control_button_down_func(int player_num, int button_num, bool repeat)
{
   //state_helper.process_key_down(button_num);



   if (!event_emitter) throw std::runtime_error("GamePlayScreen:: no event_emitter");

   auto &GAMER_BUTTON_UP = AllegroFlare::VirtualControls::BUTTON_UP;
   auto &GAMER_BUTTON_DOWN = AllegroFlare::VirtualControls::BUTTON_DOWN;
   auto &GAMER_BUTTON_LEFT = AllegroFlare::VirtualControls::BUTTON_LEFT;
   auto &GAMER_BUTTON_RIGHT = AllegroFlare::VirtualControls::BUTTON_RIGHT;
   auto &GAMER_BUTTON_A = AllegroFlare::VirtualControls::BUTTON_A;
   auto &GAMER_BUTTON_START = AllegroFlare::VirtualControls::BUTTON_START;

   switch (state)
   {
   case GamePlayScreen::GAME_PLAY:
      if (button_num == GAMER_BUTTON_START) event_emitter->emit_event(OPEN_INVENTORY_SCREEN);
      else
      {
         if (button_num == GAMER_BUTTON_UP) up_pressed = true;
         if (button_num == GAMER_BUTTON_DOWN) down_pressed = true;
         if (button_num == GAMER_BUTTON_LEFT) left_pressed = true;
         if (button_num == GAMER_BUTTON_RIGHT) right_pressed = true;
         player_krampus_controller.on_key_down(button_num);
      }
      break;
   case GamePlayScreen::ENTERING_THROUGH_DOOR:
      // nothing
      break;
   case GamePlayScreen::INVENTORY_SCREEN:
      if (button_num == GAMER_BUTTON_UP) event_emitter->emit_event(INVENTORY_SCREEN__MOVE_CURSOR_UP);
      if (button_num == GAMER_BUTTON_DOWN) event_emitter->emit_event(INVENTORY_SCREEN__MOVE_CURSOR_DOWN);
      if (button_num == GAMER_BUTTON_LEFT) event_emitter->emit_event(INVENTORY_SCREEN__MOVE_CURSOR_LEFT);
      if (button_num == GAMER_BUTTON_RIGHT) event_emitter->emit_event(INVENTORY_SCREEN__MOVE_CURSOR_RIGHT);
      if (button_num == GAMER_BUTTON_A) event_emitter->emit_event(INVENTORY_SCREEN__SELECT_ITEM);
      if (button_num == GAMER_BUTTON_START) event_emitter->emit_event(CLOSE_INVENTORY_SCREEN);
      break;
   case GamePlayScreen::ITEM_COLLECTED:
       // can only close dialogue after a delay
      if (_can_bypass_dialogue()
         && (button_num == GAMER_BUTTON_A || button_num == GAMER_BUTTON_START))
      {
         SceneCollectionHelper collections(scene);
         KrampusEntity *krampus = collections.get_krampus();
         if (krampus) krampus->stand_still();
         camera.zoom_to(1.0, 0.6);
         camera.tilt_to(0.0, 0.3);
         set_state(GamePlayScreen::GAME_PLAY);
      }
      break;
   case GamePlayScreen::GAME_LOST:
       // can only close dialogue after a delay
      if (_can_bypass_dialogue()
         && (button_num == GAMER_BUTTON_A || button_num == GAMER_BUTTON_START))
      {
         event_emitter->emit_event(START_TITLE_SCREEN);
      }
      break;
   case GamePlayScreen::GAME_WON:
       // can only close dialogue after a delay
      if (_can_bypass_dialogue()
         && (button_num == GAMER_BUTTON_A || button_num == GAMER_BUTTON_START))
      {
         event_emitter->emit_event(START_CLOSING_STORYBOARD_SCREEN);
      }
      break;
   default:
      break;
   }





   //switch (event->user.type)
   //{
      //case ALLEGRO_FLARE_EVENT_VIRTUAL_CONTROL_BUTTON_DOWN:
      //{
         //int user_input = event->user.data1;
         //state_helper.process_key_down(user_input);
         //break;
      //}
      ////case ALLEGRO_EVENT_GAMER_BUTTON_UP:
      //case ALLEGRO_FLARE_EVENT_VIRTUAL_CONTROL_BUTTON_UP:
      //{
         //switch (state)
         //{
            //case GAME_PLAY:
            //{
               //int user_input = event->user.data1;
               //player_krampus_controller.on_key_up(user_input);
               //break;
            //}
            //default: break;
         //}
         //break;
      //}
   //}
}




void GamePlayScreen::virtual_control_axis_change_func(ALLEGRO_EVENT *ev)
{
   ALLEGRO_EVENT *event = ev;
}



void GamePlayScreen::key_down_func(ALLEGRO_EVENT *ev)
{
   switch (ev->keyboard.keycode)
   {
      case ALLEGRO_KEY_D:
         debugger_active = true;
      break;
   }
}




void GamePlayScreen::user_event_func(ALLEGRO_EVENT *ev)
{
   //std::cout << "EVENT! " << std::endl;


   ALLEGRO_EVENT *event = ev;

   switch (event->user.type)
   {
      case PLAYER_DIED_EVENT:
      {
         set_state(GAME_LOST);
      }
      break;
      //case ALLEGRO_EVENT_GAMER_BUTTON_DOWN:
      //case ALLEGRO_FLARE_EVENT_VIRTUAL_CONTROL_BUTTON_DOWN:
      //{
         //int user_input = event->user.data1;
         //state_helper.process_key_down(user_input);
         //break;
      //}
      ////case ALLEGRO_EVENT_GAMER_BUTTON_UP:
      //case ALLEGRO_FLARE_EVENT_VIRTUAL_CONTROL_BUTTON_UP:
      //{
         //switch (state)
         //{
            //case GAME_PLAY:
            //{
               //int user_input = event->user.data1;
               //player_krampus_controller.on_key_up(user_input);
               //break;
            //}
            //default: break;
         //}
         //break;
      //}
      case ENTER_DOOR_EVENT:
      {
         //std::cout << "DOOR!" << std::endl;
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



void GamePlayScreen::update()
{
   //state_helper.update_state();


   float previous_state_counter = state_counter;
   state_counter += 1.0 / 60.0;
   int __dirty_player_health = 10;

   switch (state)
   {
   case GamePlayScreen::GAME_PLAY:
      {
         // TODO;
         // CRITICAL:
         // OK, serious flaw, this needs to be updated:
         //bool up_pressed = false;
         //bool down_pressed = false;
         //bool left_pressed = false;
         //bool right_pressed = false;
         //game_play_screen->player_krampus_controller.update_polled_keyboard_input(gamer_input_screen);
         //bool right_pressed, bool left_pressed, bool up_pressed, bool down_pressed
         player_krampus_controller.update_polled_keyboard_input(
               right_pressed,
               left_pressed,
               up_pressed,
               down_pressed
            );
         update_scene();
         check_for_win_or_loss_condition();
      }
      break;
   case GamePlayScreen::ITEM_COLLECTED:
      {
         SceneCollectionHelper collections(scene);
         KrampusEntity *krampus = collections.get_krampus();
         if (krampus) krampus->update();
      }
      break;
   case GamePlayScreen::ENTERING_THROUGH_DOOR:
      {
         SceneCollectionHelper collections(scene);
         KrampusEntity *krampus = collections.get_krampus();
         if (previous_state_counter < 0.3 && state_counter >= 0.3)
         {
            krampus->walk_down();
         }
         if (previous_state_counter < 0.7 && state_counter >= 0.7)
         {
            if (krampus) krampus->stand_still();
         }
         if (previous_state_counter < 0.9 && state_counter >= 0.9)
         {
            set_state(GamePlayScreen::GAME_PLAY);
         }
         update_scene();
      }
      break;
   case GamePlayScreen::USING_STONE_OF_DEFIANCE:
      update_scene();
      if (previous_state_counter < 2.0 && state_counter >= 2.0)
      {
         camera.zoom_to(1.0, 3.0);
         camera.fade_to_clear(1.5);
         set_state(GamePlayScreen::GAME_PLAY);
      }
      break;
   case GamePlayScreen::GAME_LOST:
      __dirty_player_health = 0;
      update_scene();
      break;
   case GamePlayScreen::GAME_WON:
      update_scene();
      break;
   default:
      break;
   }

   // always update the camera, regardless of state
   camera.update(scene->get_width());

   // always update the hud, regardless of state
   hud.set_values(__dirty_player_health, 10);

   // always update the inventory screen, regardless of state
   // NOTE this use of al_get_time();
   inventory_screen.update(al_get_time()); //Framework::time_now);


}
//void GamePlayScreen::update(GamerInputScreen *gamer_input_screen)
//{
   //state_helper.update_state(gamer_input_screen);
//}




void GamePlayScreen::update_scene()
{
   if (!scene) return;

   for (auto &ai_controller : ai_controllers)
      ai_controller->update();

   scene->update_all();

   // destroy the AI controllers for enemies flagged for deletion
   // OK, there's some unusaly complexity here.  In this instance
   // we want to be sure that an AIController is deleted from the
   // enemy if it is flagged for deletion.  Also, we want kids names
   // to be removed from the list when they're killed as well.  That
   // should probably be an emitted event
   SceneCollectionHelper collections(scene);
   for (auto &enemy : collections.get_enemies_flagged_for_deletion())
   {
      // "kill" the kid off from the naughty list
      if (enemy->exists("type", "kid"))
      {
         KidEntity *kid = static_cast<KidEntity *>(enemy);
         naughty_list.kill_kid_by_name(kid->get_name());
      }

      // destroy the ai controller
      _destroy_ai_controller(enemy);
   }

   // now remove all the entities
   scene->cleanup_all();
}



void GamePlayScreen::draw_scene_with_camera()
{
   camera.start_transform();
   scene->draw_all();
   camera.restore_transform();
}



void GamePlayScreen::check_for_win_or_loss_condition()
{
   if (naughty_list.are_any_nice_kids_killed())
      set_state(GamePlayScreen::GAME_LOST);
   else if (naughty_list.are_all_naughty_kids_killed())
      set_state(GamePlayScreen::GAME_WON);
}



bool GamePlayScreen::_can_bypass_dialogue()
{
   return state_counter > 3.0;
}







void GamePlayScreen::draw()
{
   //state_helper.draw_state();

   //al_clear_to_color(AllegroFlare::color::black); // not needed because allegro flare clears automatically

   switch (state)
   {
   case GamePlayScreen::GAME_PLAY:
      {
         if (scene) draw_scene_with_camera();
         break;
      }
   case GamePlayScreen::INVENTORY_SCREEN:
      {
         if (scene) draw_scene_with_camera();
         inventory_screen.draw(); //display);
         break;
      }
   case GamePlayScreen::ITEM_COLLECTED:
      {
         if (scene) draw_scene_with_camera();
         ItemDialogue dialogue = DialogueFactory::build_collected_item_dialog(_item_recently_collected);
         if (_can_bypass_dialogue()) dialogue.set_showing_continue_notification();
         dialogue.draw(0);
         break;
      }
   case GamePlayScreen::ENTERING_THROUGH_DOOR:
      {
         if (scene) draw_scene_with_camera();
         break;
      }
   case GamePlayScreen::USING_STONE_OF_DEFIANCE:
      {
         if (scene) draw_scene_with_camera();
         break;
      }
   case GamePlayScreen::GAME_LOST:
      {
         if (scene) draw_scene_with_camera();
         ItemDialogue dialogue = DialogueFactory::build_dialogue("\n\n               Game Over");
         if (_can_bypass_dialogue()) dialogue.set_showing_continue_notification();
         dialogue.draw(0);
         break;
      }
   case GamePlayScreen::GAME_WON:
      {
         if (scene) draw_scene_with_camera();
         ItemDialogue dialogue = DialogueFactory::build_dialogue("Awesome!!\n\nYou did it! You punished all the naughty children on the naughty list!");
         if (_can_bypass_dialogue()) dialogue.set_showing_continue_notification();
         dialogue.draw(0);
         break;
      }
   default:
      break;
   }

   // draw the camera's overlay color
   camera.draw_overlay();

   // note the hud is always displayed over the camera
   hud.draw();
}



void GamePlayScreen::set_state(state_t new_state)
{
   //state_helper.set_state(new_state);
   state = (GamePlayScreen::state_t)new_state;
   state_counter = 0.0;

   switch (state)
   {
   case GamePlayScreen::GAME_PLAY:
      hud.set_to_game_play_mode();
      break;
   case GamePlayScreen::INVENTORY_SCREEN:
      hud.set_to_game_play_mode();
      break;
   case GamePlayScreen::ITEM_COLLECTED:
      {
         SceneCollectionHelper collections(scene);
         KrampusEntity *krampus = collections.get_krampus();
         if (krampus) krampus->celebrate();
         event_emitter->emit_event(PLAY_SOUND_EFFECT, TADA_SOUND_EFFECT);
         hud.set_to_cinema_mode();
         camera.zoom_to(0.6, 0.3);
         camera.tilt_to(random.get_random_bool() ? 0.1 : -0.1, 0.3);
      }
      break;
   case GamePlayScreen::ENTERING_THROUGH_DOOR:
      camera.set_overlay_color(AllegroFlare::color::black);
      hud.set_to_cinema_mode();
      camera.fade_to_clear(1.5);
      camera.set_zoom(0.8);
      camera.zoom_to(1.0, 2.2);
      break;
   case GamePlayScreen::USING_STONE_OF_DEFIANCE:
      {
         camera.zoom_to(1.15, 0.3);
         camera.set_overlay_color(AllegroFlare::color::color(AllegroFlare::color::mix(AllegroFlare::color::red, AllegroFlare::color::violet, 0.5), 0.2));
         SceneCollectionHelper collections(scene);
         for (auto &kid : collections.get_kids()) kid->reveal_behavior();
      }
      break;
   case GamePlayScreen::GAME_LOST:
      event_emitter->emit_event(PLAY_SOUND_EFFECT, 0, (intptr_t)(new std::string(FAIL_MOAN_SOUND_EFFECT)));
      camera.set_overlay_color(AllegroFlare::color::color(AllegroFlare::color::red, 0.3));
      camera.zoom_to(0.8, 2.2);
      camera.tilt_to(random.get_random_bool() ? 0.03 : -0.03, 2.0);
      break;
   case GamePlayScreen::GAME_WON:
      {
         SceneCollectionHelper collections(scene);
         KrampusEntity *krampus = collections.get_krampus();
         if (krampus) krampus->celebrate();
         event_emitter->emit_event(PLAY_SOUND_EFFECT, WIN_CHEER_SOUND_EFFECT);
         camera.set_overlay_color(AllegroFlare::color::color(AllegroFlare::color::white, 0.1));
         camera.zoom_to(1.1, 5.0);
      }
      break;
   default:
      break;
   }

}



void GamePlayScreen::enter_scene(int scene_id, char door_name)
{
   if (scene) delete scene;

   SceneFactory::set_event_emitter(event_emitter);

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
      krampus->place.position = door->place.position + AllegroFlare::Vec2D{ 0.0, door->place.size.y/2 + krampus->place.size.y/2 } + 5;
   }

   set_state(ENTERING_THROUGH_DOOR);
}


AllegroFlare::Shader *GamePlayScreen::get_flat_color_shader()
{
   return &flat_color_shader;
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



