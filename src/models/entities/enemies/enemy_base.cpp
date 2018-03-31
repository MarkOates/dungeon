

#include <models/entities/enemies/enemy_base.hpp>


EnemyBase::EnemyBase(ElementID *parent, std::string enemy_type, float x, float y, int health)
   : EntityBase(parent, "enemy_base", x, y)
   , health(health)
{
   set("enemy_type", enemy_type);
}


EnemyBase::~EnemyBase()
{
}


void EnemyBase::take_hit()
{
}


int EnemyBase::get_health()
{
   return health;
}


