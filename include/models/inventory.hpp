#pragma once



#include <string>
#include <vector>



class Inventory
{
public:
   std::vector<int> items;

   int equipped_weapon;
   int equipped_shield;
   int equipped_item;

public:
   Inventory();

   void add_item(int item_type);
   bool has_item(int item_type);

   int get_ordered_item(int item_index);

   int get_equipped_weapon();
   int get_equipped_shield();
   int get_equipped_item();

   void set_equipped_weapon(int weapon_item);
   void set_equipped_shield(int shield_item);
   void set_equipped_item(int item_item);

   std::string get_str();
};



