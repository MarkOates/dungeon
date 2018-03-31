#pragma once



#include <models/entities/krampus_entity.hpp>



class GamerInputScreen;



class PlayerKrampusController
{
private:
   KrampusEntity *krampus;

public:
   PlayerKrampusController();

   void set_krampus(KrampusEntity *krampus);
   bool has_a_krampus();

   void on_key_down(int input_button);
   void on_key_up(int input_button);

   void update_polled_keyboard_input(GamerInputScreen *gamer_input_screen);
};



