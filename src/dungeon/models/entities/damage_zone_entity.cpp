


#include <dungeon/models/entities/damage_zone_entity.hpp>

#include <dungeon/entity_attribute_names.hpp>



DamageZoneEntity::DamageZoneEntity(AllegroFlare::ElementID *parent, std::string damage_zone_type, bool damages_krampus, bool damages_enemies, float x, float y, float w, float h, direction_of_force_t direction_of_force)
   : Entity::Base(parent, "damage_zone", x, y)
   , direction_of_force(direction_of_force)
   , dealing_damage(true)
{
   //place.size = vec2d(w, h);
   place.size = { w, h };
   set("damage_zone_type", damage_zone_type);
   if (damages_krampus) set(DAMAGES_KRAMPUS);
   if (damages_enemies) set(DAMAGES_ENEMIES);
}



DamageZoneEntity::~DamageZoneEntity()
{
}



void DamageZoneEntity::draw()
{
   Entity::Base::draw();
}



void DamageZoneEntity::update()
{
   if (!dealing_damage) flag_for_deletion();
   if (dealing_damage) dealing_damage = false;
}



bool DamageZoneEntity::is_dealing_damage()
{
   return dealing_damage;
}



int DamageZoneEntity::get_damage(float x, float y)
{
   return 1;
}



bool DamageZoneEntity::is_krampus_damage_zone()
{
   return exists("damage_zone_type", "krampus_damage_zone");
}



bool DamageZoneEntity::is_krampus_damage_zone_with_club()
{
   return exists("damage_zone_type", "krampus_damage_zone_club");
}



