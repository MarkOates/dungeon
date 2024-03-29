


#include <dungeon/factories/scene_factory.hpp>

#include <dungeon/models/entities/base.hpp>
#include <dungeon/factories/entity_factory.hpp>



float SceneFactory::door_notch_x(int pos)
   // door_notch_x is a convience function for easily
   // getting an x coordintate for placing a door
{
   if (!event_emitter) throw std::runtime_error("SceneFactory no event_emitter");

   float door_spacing = ONE_SCREEN_WIDTH / 6.0;
   return door_spacing + (door_spacing * 2) * pos;
}




Scene *SceneFactory::_create_scene_by_dimentions(int screen_widths, int background_type)
{
   if (!event_emitter) throw std::runtime_error("SceneFactory no event_emitter");

   Scene *scene = new Scene(event_emitter, ONE_SCREEN_WIDTH*screen_widths);

   // background
   for (int i=-1; i<(screen_widths+1); i++)
   {
      switch (background_type)
      {
      case 1: EntityFactory::create_background1(scene, i*ONE_SCREEN_WIDTH, 0); break;
      case 2: EntityFactory::create_background2(scene, i*ONE_SCREEN_WIDTH, 0); break;
      case 3: EntityFactory::create_background3(scene, i*ONE_SCREEN_WIDTH, 0); break;
      case 4: EntityFactory::create_background4(scene, i*ONE_SCREEN_WIDTH, 0); break;
      case 5: EntityFactory::create_background5(scene, i*ONE_SCREEN_WIDTH, 0); break;
      case 6: EntityFactory::create_background6(scene, i*ONE_SCREEN_WIDTH, 0); break;
      default: EntityFactory::create_background1(scene, i*ONE_SCREEN_WIDTH, 0); break;
      }
   }

   return scene;
}



Scene *SceneFactory::create_test_scene()
{
   if (!event_emitter) throw std::runtime_error("SceneFactory no event_emitter");

   Scene *scene = _create_scene_by_dimentions(2);

   // enemies
   for (unsigned i=0; i<20; i++)
      EntityFactory::create_random_kid(scene, random.get_random_float(200, 900), random.get_random_float(400, 600));

   // doors
   EntityFactory::create_door1(scene, door_notch_x(0), FLOOR_TOP, "A", 999, "A");

   // items
   EntityFactory::create_club_item(scene, 800, 565);
   EntityFactory::create_naughty_list_item(scene, 900, 565);
   EntityFactory::create_stone_of_defiance_item(scene, 1000, 565);
   EntityFactory::create_key_item(scene, 1100, 565);

   return scene;
}



Scene *SceneFactory::create_scene_by_id(int scene_id)
{
   if (!event_emitter) throw std::runtime_error("SceneFactory no event_emitter");

   Scene *scene = nullptr;

   switch (scene_id)
   {
   case 0: scene = SceneFactory::create_scene_0(); break;
   case 1: scene = SceneFactory::create_scene_1(); break;
   case 2: scene = SceneFactory::create_scene_2(); break;
   case 3: scene = SceneFactory::create_scene_3(); break;
   case 4: scene = SceneFactory::create_scene_4(); break;
   case 5: scene = SceneFactory::create_scene_5(); break;
   case 6: scene = SceneFactory::create_scene_6(); break;
   case 7: scene = SceneFactory::create_scene_7(); break;
   case 8: scene = SceneFactory::create_scene_8(); break;
   case 9: scene = SceneFactory::create_scene_9(); break;
   case 999: scene = SceneFactory::create_test_scene(); break;
   default: break;
   }

   // player
   EntityFactory::create_krampus(scene, 600, 600);

   return scene;
}



void SceneFactory::set_event_emitter(AllegroFlare::EventEmitter *event_emitter)
{
   SceneFactory::event_emitter = event_emitter;
}



Scene *SceneFactory::create_scene_0()
{
   if (!event_emitter) throw std::runtime_error("SceneFactory no event_emitter");

   Scene *scene = _create_scene_by_dimentions(1, 2);

   // doors
   EntityFactory::create_door5(scene, door_notch_x(2), FLOOR_TOP, "A", 1, "a");
   EntityFactory::create_skull_enemy(scene, ONE_SCREEN_WIDTH-5, 565, FLOOR_TOP, FLOOR_BOTTOM);
   EntityFactory::create_blob(scene, ONE_SCREEN_WIDTH-200, FLOOR_MIDDLE);

   return scene;
}



Scene *SceneFactory::create_scene_1()
   // master corridor
{
   if (!event_emitter) throw std::runtime_error("SceneFactory no event_emitter");

   Scene *scene = _create_scene_by_dimentions(4, 1);

   // doors
   EntityFactory::create_door1(scene, door_notch_x(0), FLOOR_TOP, "F", 2, "f");
   EntityFactory::create_door4(scene, door_notch_x(4), FLOOR_TOP, "E", 9, "e"); // big santa door
   EntityFactory::create_door6(scene, door_notch_x(8), FLOOR_TOP, "a", 0, "A");
   EntityFactory::create_door1(scene, door_notch_x(11), FLOOR_TOP, "B", 3, "b");

   return scene;
}



Scene *SceneFactory::create_scene_2()
{
   if (!event_emitter) throw std::runtime_error("SceneFactory no event_emitter");

   Scene *scene = _create_scene_by_dimentions(2, 4);

   // doors
   EntityFactory::create_door2(scene, door_notch_x(0), FLOOR_TOP, "G", 4, "g");
   EntityFactory::create_door2(scene, door_notch_x(5), FLOOR_TOP, "f", 1, "F");

   return scene;
}



Scene *SceneFactory::create_scene_3()
{
   if (!event_emitter) throw std::runtime_error("SceneFactory no event_emitter");

   Scene *scene = _create_scene_by_dimentions(2, 3);

   // doors
   EntityFactory::create_door3(scene, door_notch_x(0), FLOOR_TOP, "b", 1, "B");
   EntityFactory::create_door3(scene, door_notch_x(4), FLOOR_TOP, "C", 7, "c");
   EntityFactory::create_door2(scene, door_notch_x(5), FLOOR_TOP, "D", 5, "d");

   return scene;
}



Scene *SceneFactory::create_scene_4()
{
   if (!event_emitter) throw std::runtime_error("SceneFactory no event_emitter");

   Scene *scene = _create_scene_by_dimentions(1, 4);

   // doors
   EntityFactory::create_door2(scene, door_notch_x(0), FLOOR_TOP, "g", 2, "G");
   EntityFactory::create_door2(scene, door_notch_x(2), FLOOR_TOP, "H", 6, "h");

   // items
   EntityFactory::create_naughty_list_item(scene, door_notch_x(1), FLOOR_MIDDLE);

   return scene;
}



Scene *SceneFactory::create_scene_5()
{
   if (!event_emitter) throw std::runtime_error("SceneFactory no event_emitter");

   Scene *scene = _create_scene_by_dimentions(1, 5);

   // doors
   EntityFactory::create_door2(scene, door_notch_x(0), FLOOR_TOP, "d", 3, "D");

   // items
   EntityFactory::create_club_item(scene, door_notch_x(1), FLOOR_MIDDLE);

   return scene;
}



Scene *SceneFactory::create_scene_6()
{
   if (!event_emitter) throw std::runtime_error("SceneFactory no event_emitter");

   Scene *scene = _create_scene_by_dimentions(1, 4);

   // doors
   EntityFactory::create_door2(scene, door_notch_x(0), FLOOR_TOP, "h", 4, "H");

   // items
   EntityFactory::create_key_item(scene, door_notch_x(1), FLOOR_MIDDLE);

   return scene;
}



Scene *SceneFactory::create_scene_7()
{
   if (!event_emitter) throw std::runtime_error("SceneFactory no event_emitter");

   Scene *scene = _create_scene_by_dimentions(3, 4);

   // doors
   EntityFactory::create_door2(scene, door_notch_x(0), FLOOR_TOP, "D", 8, "d");
   EntityFactory::create_door2(scene, door_notch_x(8), FLOOR_TOP, "c", 3, "C");

   return scene;
}



Scene *SceneFactory::create_scene_8()
{
   if (!event_emitter) throw std::runtime_error("SceneFactory no event_emitter");

   Scene *scene = _create_scene_by_dimentions(1, 4);

   // doors
   EntityFactory::create_door2(scene, door_notch_x(0), FLOOR_TOP, "d", 7, "D");

   // items
   EntityFactory::create_stone_of_defiance_item(scene, door_notch_x(1), FLOOR_MIDDLE);

   return scene;
}



Scene *SceneFactory::create_scene_9()
{
   if (!event_emitter) throw std::runtime_error("SceneFactory no event_emitter");

   Scene *scene = _create_scene_by_dimentions(2, 6);

   // doors
   EntityFactory::create_door1(scene, door_notch_x(5), FLOOR_TOP, "e", 1, "E");  // external big santa door

   return scene;
}


AllegroFlare::EventEmitter *SceneFactory::event_emitter = nullptr;
AllegroFlare::Random SceneFactory::random;

