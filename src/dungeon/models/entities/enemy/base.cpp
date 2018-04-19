

#include <dungeon/models/entities/enemy/base.hpp>


namespace Enemy
{


Base::Base(ElementID *parent, std::string enemy_type, float x, float y, int health)
   : EntityBase(parent, "enemy_base", x, y)
   , health(health)
{
   set("enemy_type", enemy_type);
}


Base::~Base()
{
}


void Base::take_hit()
{
}


int Base::get_health()
{
   return health;
}


} // namespace Enemy


