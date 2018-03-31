#pragma once



#include <models/scene.hpp>
#include <helpers/scene_collection_helper.hpp>



class SceneCollisionHelper
{
private:
   Scene *scene;
   SceneCollectionHelper collections;

   void update_entities();
   void limit_sprites_to_world_bounds();
   void check_damage_zones_on_enemies();
   void check_damage_zones_on_krampus();
   void check_krampus_on_door();
   void check_krampus_on_items();

public:
   SceneCollisionHelper(Scene *scene);

   void resolve_collisions();
};



