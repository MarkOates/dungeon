#pragma once


#include <dungeon/models/entities/enemy/knight_entity.hpp>
#include <dungeon/entity_controllers/ai_controller_base.hpp>
#include <AllegroFlare/Random.hpp>


class AIKnightController : public AIControllerBase
{
private:
   AllegroFlare::Random random;
   float state_counter;
   KnightEntity *knight;
   KnightEntity::state_t _get_a_random_state();
   KnightEntity::state_t _get_a_random_state_different_from_current_one();
   void set_new_state();

public:
   AIKnightController(KnightEntity *knight);

   void update() override;
};


