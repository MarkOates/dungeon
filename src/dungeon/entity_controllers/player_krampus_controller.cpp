


#include <dungeon/entity_controllers/player_krampus_controller.hpp>

//#include <framework/screens/gamer_input_screen.hpp>

#include <AllegroFlare/VirtualControls.hpp>



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

   auto &GAMER_BUTTON_UP = AllegroFlare::VirtualControls::BUTTON_UP;
   auto &GAMER_BUTTON_DOWN = AllegroFlare::VirtualControls::BUTTON_DOWN;
   auto &GAMER_BUTTON_LEFT = AllegroFlare::VirtualControls::BUTTON_LEFT;
   auto &GAMER_BUTTON_RIGHT = AllegroFlare::VirtualControls::BUTTON_RIGHT;
   auto &GAMER_BUTTON_A = AllegroFlare::VirtualControls::BUTTON_A;
   auto &GAMER_BUTTON_B = AllegroFlare::VirtualControls::BUTTON_B;
   auto &GAMER_BUTTON_X = AllegroFlare::VirtualControls::BUTTON_X;
   auto &GAMER_BUTTON_START = AllegroFlare::VirtualControls::BUTTON_START;
   

   // TODO: THIS
   switch(input_button)
   {
   case GAMER_BUTTON_A: krampus->attack(); break;
   case GAMER_BUTTON_B: krampus->block(); break;
   case GAMER_BUTTON_X: krampus->use_stone_of_defiance(); break; // note: was GAMER_BUTTON_C
   case GAMER_BUTTON_UP: krampus->walk_up(); break;
   case GAMER_BUTTON_DOWN: krampus->walk_down(); break;
   case GAMER_BUTTON_RIGHT: krampus->walk_right(); break;
   case GAMER_BUTTON_LEFT: krampus->walk_left(); break;
   default: break;
   }
}



void PlayerKrampusController::on_key_up(int input_button)
{
   if (!has_a_krampus()) return;

   auto &GAMER_BUTTON_UP = AllegroFlare::VirtualControls::BUTTON_UP;
   auto &GAMER_BUTTON_DOWN = AllegroFlare::VirtualControls::BUTTON_DOWN;
   auto &GAMER_BUTTON_LEFT = AllegroFlare::VirtualControls::BUTTON_LEFT;
   auto &GAMER_BUTTON_RIGHT = AllegroFlare::VirtualControls::BUTTON_RIGHT;
   auto &GAMER_BUTTON_A = AllegroFlare::VirtualControls::BUTTON_A;
   auto &GAMER_BUTTON_B = AllegroFlare::VirtualControls::BUTTON_B;
   auto &GAMER_BUTTON_START = AllegroFlare::VirtualControls::BUTTON_START;



   // TODO: THIS
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



void PlayerKrampusController::update_polled_keyboard_input(bool right_pressed, bool left_pressed, bool up_pressed, bool down_pressed)
{
   //if (!gamer_input_screen) throw std::runtime_error("PlayerKrampusController::update_polled_keyboard_input() cannot is_pressed() on a nullptr gamer_input_screen");

   //if (krampus->is_idle())
   //{
      //if (right_pressed) krampus->walk_right();
      //if (left_pressed) krampus->walk_left();
      //if (up_pressed) krampus->walk_up();
      //if (down_pressed) krampus->walk_down();
   //}
}



