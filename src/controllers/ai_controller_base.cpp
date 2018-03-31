


#include <controllers/ai_controller_base.hpp>



AIControllerBase::AIControllerBase(EntityBase *entity)
   : entity(entity)
{
}



AIControllerBase::~AIControllerBase()
{
}



void AIControllerBase::update()
{
}



bool AIControllerBase::is_controlling(EntityBase *possibly_controlled_entity)
{
   return entity == possibly_controlled_entity;
}



