


#include <dungeon/helpers/scene_collision_helper.hpp>

#include <dungeon/emitters/user_event_emitter.hpp>
#include <dungeon/models/entities/enemy/kid_entity.hpp>
#include <dungeon/models/entities/damage_zone_entity.hpp>
#include <dungeon/models/entities/base.hpp>
#include <dungeon/models/entities/door_entity.hpp>
#include <dungeon/models/entities/krampus_entity.hpp>
#include <dungeon/helpers/scene_collection_helper.hpp>
#include <dungeon/user_events.hpp>



SceneCollisionHelper::SceneCollisionHelper(AllegroFlare::EventEmitter *event_emitter, Scene *scene)
   : scene(scene)
   , collections(scene)
   , event_emitter(event_emitter)
{
   if (!event_emitter) throw std::runtime_error("SceneCollisionHelper no event_emitter");
}



void SceneCollisionHelper::resolve_collisions()
{
   if (!scene) return;

   update_entities();
   limit_sprites_to_world_bounds();
   check_damage_zones_on_enemies();
   check_damage_zones_on_krampus();
   check_krampus_on_door();
   check_krampus_on_items();
};



void SceneCollisionHelper::update_entities()
{
   for (auto &entity : collections.get_all_entities())
      entity->update();
}



void SceneCollisionHelper::limit_sprites_to_world_bounds()
{
   float min_y, max_y;
   scene->get_y_bounds(&min_y, &max_y);
   float max_x = scene->get_width();

   for (auto &entity : collections.get_entities_bound_in_world())
   {
      if (entity->place.position.y < min_y) entity->place.position.y = min_y;
      if (entity->place.position.y > max_y) entity->place.position.y = max_y;
      if (entity->place.position.x < 0) entity->place.position.x = 0;
      if (entity->place.position.x > max_x) entity->place.position.x = max_x;
   }
}



void SceneCollisionHelper::check_damage_zones_on_enemies()
{
   // damage zone <-> enemy collisions
   for (auto &damage_zone : collections.get_all_damage_zones_that_damage_enemies())
   {
      for (auto &enemy : collections.get_enemies())
      {
         if (damage_zone->is_dealing_damage() && damage_zone->collides(*enemy))
         {
            if (damage_zone->is_krampus_damage_zone()) enemy->take_hit();
            else if (damage_zone->is_krampus_damage_zone_with_club()) enemy->flag_for_deletion();
         }
      }
   }
}



void SceneCollisionHelper::check_damage_zones_on_krampus()
{
   KrampusEntity *krampus = collections.get_krampus();

   // damage zone <-> krampus collisions
   for (auto &damage_zone : collections.get_all_damage_zones_that_damage_krampus())
   {
      if (damage_zone->collides(*krampus))
      {
         krampus->take_hit();
      }
   }
}



void SceneCollisionHelper::check_krampus_on_door()
{
   KrampusEntity *krampus = collections.get_krampus();
   for (auto &door : collections.get_doors())
   {
      if (door->place.collide(krampus->place.position.x, krampus->place.position.y))
      {
         std::cout << "COLLIDE!" << std::endl;
         int destination_scene = door->get_as_int("destination_scene");
         std::string destination_door_name = door->get_as_string("destination_door_name");
         char dest_door_char = destination_door_name.size() == 1 ? destination_door_name[0] : '!';

         event_emitter->emit_event(ENTER_DOOR_EVENT, destination_scene, dest_door_char);
      }
   }
}



void SceneCollisionHelper::check_krampus_on_items()
{
   KrampusEntity *krampus = collections.get_krampus();
   for (auto &item : collections.get_items())
   {
      if (item->place.collide(krampus->place.position.x, krampus->place.position.y, 20, 10, 20, 10))
      {
         int item_type_int = item->get_as_int("item_type_int");
         event_emitter->emit_event(COLLECT_ITEM_EVENT, item_type_int);
         item->flag_for_deletion();
      }
   }
}



