#pragma once



class EntityBase;



class AIControllerBase
{
private:
   EntityBase *entity;

public:
   AIControllerBase(EntityBase *entity);
   virtual ~AIControllerBase();

   virtual void update();
   bool is_controlling(EntityBase *possibly_controlled_entity);
};



