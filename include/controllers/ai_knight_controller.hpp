#pragma once



#include <models/entities/enemies/knight_entity.hpp>
#include <controllers/ai_controller_base.hpp>



class AIKnightController : public AIControllerBase
{
private:
   float state_counter;
   KnightEntity *knight;
   KnightEntity::state_t _get_a_random_state();
   KnightEntity::state_t _get_a_random_state_different_from_current_one();
   void set_new_state();

public:
   AIKnightController(KnightEntity *knight);

   void update() override;
};



