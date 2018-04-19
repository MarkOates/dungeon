#pragma once


#include <dungeon/models/entities/base.hpp>


namespace Enemy
{
   class Base : public Entity::Base
   {
   private:
      int health;

   public:
      Base(ElementID *parent, std::string enemy_type, float x, float y, int health=1);
      virtual ~Base();

      virtual void take_hit();
      int get_health();
   };
}


