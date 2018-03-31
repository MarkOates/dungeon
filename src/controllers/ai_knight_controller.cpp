


#include <controllers/ai_knight_controller.hpp>



AIKnightController::AIKnightController(KnightEntity *knight)
   : AIControllerBase(knight)
   , knight(knight)
   , state_counter(0.0)
{}



KnightEntity::state_t AIKnightController::_get_a_random_state()
{
   std::vector<KnightEntity::state_t> possible_states = {
         KnightEntity::STATE_ATTACKING,
         KnightEntity::STATE_STANDING_STILL,
         KnightEntity::STATE_WALKING_UP,
         KnightEntity::STATE_WALKING_DOWN,
         //KnightEntity::STATE_WALKING_LEFT,
         //KnightEntity::STATE_WALKING_RIGHT
      };

   if (possible_states.size() <= 1) throw std::runtime_error("AIKnightController::_get_a_random_state() cannot contain 1 or fewer items.");

   return possible_states[random_int(0, possible_states.size()-1)];
}



KnightEntity::state_t AIKnightController::_get_a_random_state_different_from_current_one()
{
   KnightEntity::state_t random_state = _get_a_random_state();
   while ((random_state = _get_a_random_state()) == knight->state);

   return random_state;
}



void AIKnightController::set_new_state()
{
   knight->set_state(_get_a_random_state_different_from_current_one());

   float duration_until_next_state_chage = random_float(0.5, 1.0);
   state_counter = duration_until_next_state_chage;
}



void AIKnightController::update()
{
   state_counter -= 1.0/60.0;

   if (state_counter <= 0 && !knight->is_busy()) set_new_state();
}



