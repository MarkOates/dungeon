


#include <dungeon/helpers/scene_collection_helper.hpp>

#include <dungeon/models/entities/enemy/base.hpp>
#include <dungeon/models/entities/enemy/knight_entity.hpp>
#include <dungeon/models/entities/enemy/kid_entity.hpp>
#include <dungeon/models/entities/damage_zone_entity.hpp>
#include <dungeon/models/entities/door_entity.hpp>
#include <dungeon/entity_attribute_names.hpp>

#include <AllegroFlare/ElementID.hpp>

using AllegroFlare::ElementID;



SceneCollectionHelper::SceneCollectionHelper(Scene *scene)
   : scene(scene)
{}



std::vector<Entity::Base *> SceneCollectionHelper::get_all_entities()
{
   return scene->get_flat_list_of_descendants<Entity::Base>();
}



std::vector<Entity::Base *> SceneCollectionHelper::get_all_entities_y_sorted()
{
   std::vector<Entity::Base *> flat_list = scene->get_flat_list_of_descendants<Entity::Base>();

   std::sort(flat_list.begin(), flat_list.end(),[](const Entity::Base *a, const Entity::Base *b)
         { return a->place.position.y < b->place.position.y; }
      );

   return flat_list;
}



std::vector<KidEntity *> SceneCollectionHelper::get_kids()
{
   return ElementID::recast_collection<KidEntity>(scene->find_all_descendants("enemy_type", "kid"));
}



std::vector<KnightEntity *> SceneCollectionHelper::get_knights()
{
   return ElementID::recast_collection<KnightEntity>(scene->find_all_descendants("enemy_type", "knight"));
}



std::vector<Enemy::Base *> SceneCollectionHelper::get_enemies()
{
   return ElementID::recast_collection<Enemy::Base>(scene->find_all_descendants("enemy_type"));
}



std::vector<DamageZoneEntity *> SceneCollectionHelper::get_all_damage_zones()
{
   return ElementID::recast_collection<DamageZoneEntity>(scene->find_all_descendants("type", "damage_zone"));
}



std::vector<DamageZoneEntity *> SceneCollectionHelper::get_all_damage_zones_that_damage_krampus()
{
   return ElementID::recast_collection<DamageZoneEntity>(scene->find_all_descendants(DAMAGES_KRAMPUS));
}



std::vector<DamageZoneEntity *> SceneCollectionHelper::get_all_damage_zones_that_damage_enemies()
{
   return ElementID::recast_collection<DamageZoneEntity>(scene->find_all_descendants(DAMAGES_ENEMIES));
}



KrampusEntity *SceneCollectionHelper::get_krampus()
{
   return static_cast<KrampusEntity *>(scene->find_first_descendant("type", "krampus"));
}



std::vector<Entity::Base *> SceneCollectionHelper::get_entities_bound_in_world()
{
   return ElementID::recast_collection<Entity::Base>(scene->find_all_descendants("bound_in_world"));
}



std::vector<Entity::Base *> SceneCollectionHelper::get_all_flagged_for_deletion()
{
   return ElementID::recast_collection<Entity::Base>(scene->find_all_descendants("can_be_deleted"));
}


std::vector<KidEntity *> SceneCollectionHelper::get_kids_flagged_for_deletion()
{
   std::vector<KidEntity* > kids_flagged_for_deletion;

   for (auto &kid : get_kids())
      if (kid->exists("can_be_deleted")) kids_flagged_for_deletion.push_back(kid);

   return kids_flagged_for_deletion;
}



std::vector<Enemy::Base *> SceneCollectionHelper::get_enemies_flagged_for_deletion()
{
   std::vector<Enemy::Base* > enemies_flagged_for_deletion;

   for (auto &enemy : get_enemies())
      if (enemy->exists("can_be_deleted")) enemies_flagged_for_deletion.push_back(enemy);

   return enemies_flagged_for_deletion;
}



std::vector<DoorEntity *> SceneCollectionHelper::get_doors()
{
   return ElementID::recast_collection<DoorEntity>(scene->find_all_descendants("type", "door"));
}



std::vector<ItemEntity *> SceneCollectionHelper::get_items()
{
   return ElementID::recast_collection<ItemEntity>(scene->find_all_descendants("type", "item"));
}



DoorEntity *SceneCollectionHelper::get_door(char door_name)
{
   return static_cast<DoorEntity *>(scene->find_first("door_name", std::string(&door_name, 1)));
            //std::tostring(door_name)));
}



