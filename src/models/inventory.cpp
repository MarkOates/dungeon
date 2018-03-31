


#include <models/inventory.hpp>

#include <sstream>
#include <set>



Inventory::Inventory()
   : items()
   , equipped_weapon(0)
   , equipped_shield(0)
   , equipped_item(0)
{}



void Inventory::add_item(int item_type)
{
   items.push_back(item_type);
}



bool Inventory::has_item(int item_type)
{
   for (unsigned i=0; i<items.size(); i++)
      if (items[i] == item_type) return true;
   return false;
}


int Inventory::get_ordered_item(int item_index)
{
   if (items.empty()) return 0;

   std::set<int> set(items.begin(), items.end());
   items.assign(set.begin(), set.end());
   if (item_index >= set.size()) return 0;

   return *std::next(set.begin(), item_index);
}



std::string Inventory::get_str()
{
   std::stringstream result;
   for (auto &i : items)
   {
      result << i << " ";
   }
   return result.str();
}



int Inventory::get_equipped_weapon()
{
   return equipped_weapon;
}



int Inventory::get_equipped_shield()
{
   return equipped_shield;
}



int Inventory::get_equipped_item()
{
   return equipped_item;
}



void Inventory::set_equipped_weapon(int item)
{
   this->equipped_weapon = item;
}



void Inventory::set_equipped_shield(int item)
{
   this->equipped_shield = item;
}



void Inventory::set_equipped_item(int item)
{
   this->equipped_item = item;
}



