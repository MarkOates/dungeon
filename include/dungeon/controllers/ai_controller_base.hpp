#pragma once


namespace Entity { class Base; }


class AIControllerBase
{
private:
   Entity::Base *entity;

public:
   AIControllerBase(Entity::Base *entity);
   virtual ~AIControllerBase();

   virtual void update();
   bool is_controlling(Entity::Base *possibly_controlled_entity);
};


