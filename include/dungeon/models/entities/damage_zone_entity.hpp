#pragma once


#include <dungeon/models/entities/base.hpp>


class DamageZoneEntity : public Entity::Base
{
public:
   enum direction_of_force_t
   {
      DIRECTION_OF_FORCE_UNDEF=0,
      DIRECTION_OF_FORCE_UP,
      DIRECTION_OF_FORCE_DOWN,
      DIRECTION_OF_FORCE_LEFT,
      DIRECTION_OF_FORCE_RIGHT,
      DIRECTION_OF_FORCE_OUT,
   };

private:
   bool dealing_damage;
   int direction_of_force;

public:
   DamageZoneEntity(AllegroFlare::ElementID *parent, std::string damage_zone_type, bool damages_krampus, bool damages_enemies, float x, float y, float w, float h, direction_of_force_t direction_of_force=DIRECTION_OF_FORCE_UNDEF);
   ~DamageZoneEntity();

   void draw() override;
   void update() override;

   bool is_dealing_damage();
   int get_damage(float x=0, float y=0);

   bool is_krampus_damage_zone();
   bool is_krampus_damage_zone_with_club();
};


