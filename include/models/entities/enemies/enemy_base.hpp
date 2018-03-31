#pragma once


#include <models/entities/entity_base.hpp>


class EnemyBase : public EntityBase
{
private:
   int health;

public:
   EnemyBase(ElementID *parent, std::string enemy_type, float x, float y, int health=1);
   virtual ~EnemyBase();

   virtual void take_hit();
   int get_health();
};


