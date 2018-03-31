#pragma once



#include <models/entities/entity_base.hpp>



class DamageZoneEntity : public EntityBase
{
private:
   bool dealing_damage;

public:
   DamageZoneEntity(ElementID *parent, std::string damage_zone_type, bool damages_krampus, bool damages_enemies, float x, float y, float w, float h);
   ~DamageZoneEntity();

   void draw() override;
   void update() override;

   bool is_dealing_damage();
   int get_damage(float x=0, float y=0);

   bool is_krampus_damage_zone();
   bool is_krampus_damage_zone_with_club();
};



