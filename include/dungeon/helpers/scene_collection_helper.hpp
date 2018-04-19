#pragma once


#include <dungeon/models/entities/base.hpp>
#include <dungeon/models/entities/item_entity.hpp>
#include <dungeon/models/entities/krampus_entity.hpp>
#include <dungeon/models/scene.hpp>


class DamageZoneEntity;
class DoorEntity;
class KidEntity;
namespace Enemy { class Base; }
class KnightEntity;


class SceneCollectionHelper
{
private:
   Scene *scene;

public:
   SceneCollectionHelper(Scene *scene);

   std::vector<Entity::Base *> get_all_entities();
   std::vector<Entity::Base *> get_all_entities_y_sorted();
   std::vector<KidEntity *> get_kids();
   std::vector<KnightEntity *> get_knights();
   std::vector<Enemy::Base *> get_enemies();
   std::vector<DamageZoneEntity *> get_all_damage_zones();
   std::vector<DamageZoneEntity *> get_all_damage_zones_that_damage_krampus();
   std::vector<DamageZoneEntity *> get_all_damage_zones_that_damage_enemies();
   std::vector<Entity::Base *> get_entities_bound_in_world();
   std::vector<Entity::Base *> get_all_flagged_for_deletion();
   std::vector<Enemy::Base *> get_enemies_flagged_for_deletion();
   std::vector<KidEntity *> get_kids_flagged_for_deletion();
   std::vector<DoorEntity *> get_doors();
   std::vector<ItemEntity *> get_items();
   KrampusEntity *get_krampus();
   DoorEntity *get_door(char door_name);
};


