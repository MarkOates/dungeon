


#include <controllers/player_krampus_controller.hpp>

#include <framework/screens/gamer_input_screen.hpp>



PlayerKrampusController::PlayerKrampusController()
   : krampus(nullptr)
{}



void PlayerKrampusController::set_krampus(KrampusEntity *new_krampus)
{
   krampus = new_krampus;
}



bool PlayerKrampusController::has_a_krampus()
{
   return krampus != nullptr;
}



void PlayerKrampusController::on_key_down(int input_button)
{
   if (!has_a_krampus()) return;

   switch(input_button)
   {
   case GAMER_BUTTON_A: krampus->attack(); break;
   case GAMER_BUTTON_B: krampus->block(); break;
   case GAMER_BUTTON_C: krampus->use_stone_of_defiance(); break;
   default: break;
   }
}



void PlayerKrampusController::on_key_up(int input_button)
{
   if (!has_a_krampus()) return;

   switch(input_button)
   {
   case GAMER_BUTTON_B: krampus->stand_still(); break;
   case GAMER_BUTTON_UP: krampus->stand_still(); break;
   case GAMER_BUTTON_DOWN: krampus->stand_still(); break;
   case GAMER_BUTTON_RIGHT: krampus->stand_still(); break;
   case GAMER_BUTTON_LEFT: krampus->stand_still(); break;
   default: break;
   }
}



void PlayerKrampusController::update_polled_keyboard_input(GamerInputScreen *gamer_input_screen)
{
   if (!gamer_input_screen) throw std::runtime_error("PlayerKrampusController::update_polled_keyboard_input() cannot is_pressed() on a nullptr gamer_input_screen");

   if (krampus->is_idle())
   {
      if (gamer_input_screen->is_pressed(GAMER_BUTTON_RIGHT)) krampus->walk_right();
      if (gamer_input_screen->is_pressed(GAMER_BUTTON_LEFT)) krampus->walk_left();
      if (gamer_input_screen->is_pressed(GAMER_BUTTON_UP)) krampus->walk_up();
      if (gamer_input_screen->is_pressed(GAMER_BUTTON_DOWN)) krampus->walk_down();
   }
}



