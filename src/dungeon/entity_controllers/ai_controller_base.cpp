


#include <dungeon/entity_controllers/ai_controller_base.hpp>



AIControllerBase::AIControllerBase(Entity::Base *entity)
   : entity(entity)
{
}



AIControllerBase::~AIControllerBase()
{
}



void AIControllerBase::update()
{
}



bool AIControllerBase::is_controlling(Entity::Base *possibly_controlled_entity)
{
   return entity == possibly_controlled_entity;
}



