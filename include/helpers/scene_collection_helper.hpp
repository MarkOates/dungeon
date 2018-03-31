#pragma once



#include <models/entities/entity_base.hpp>
#include <models/entities/item_entity.hpp>
#include <models/entities/krampus_entity.hpp>
#include <models/scene.hpp>



class DamageZoneEntity;
class DoorEntity;
class KidEntity;
class EnemyBase;
class KnightEntity;



class SceneCollectionHelper
{
private:
   Scene *scene;

public:
   SceneCollectionHelper(Scene *scene);

   std::vector<EntityBase *> get_all_entities();
   std::vector<EntityBase *> get_all_entities_y_sorted();
   std::vector<KidEntity *> get_kids();
   std::vector<KnightEntity *> get_knights();
   std::vector<EnemyBase *> get_enemies();
   std::vector<DamageZoneEntity *> get_all_damage_zones();
   std::vector<DamageZoneEntity *> get_all_damage_zones_that_damage_krampus();
   std::vector<DamageZoneEntity *> get_all_damage_zones_that_damage_enemies();
   std::vector<EntityBase *> get_entities_bound_in_world();
   std::vector<EntityBase *> get_all_flagged_for_deletion();
   std::vector<EnemyBase *> get_enemies_flagged_for_deletion();
   std::vector<KidEntity *> get_kids_flagged_for_deletion();
   std::vector<DoorEntity *> get_doors();
   std::vector<ItemEntity *> get_items();
   KrampusEntity *get_krampus();
   DoorEntity *get_door(char door_name);
};



