#pragma once


#include <dungeon/models/entities/enemy/kid_entity.hpp>
#include <dungeon/entity_controllers/ai_controller_base.hpp>


class AIKidController : public AIControllerBase
{
private:
   float state_counter;
   KidEntity *kid;
   KidEntity::state_t _get_a_random_state();
   KidEntity::state_t _get_a_random_state_different_from_current_one();
   void set_new_state();

public:
   AIKidController(KidEntity *kid);

   void update() override;
};


