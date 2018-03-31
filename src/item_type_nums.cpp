


#include <item_type_nums.hpp>



int get_item_sprite_num(int item_num)
{
   switch (item_num)
   {
   ITEM_TYPE_WOODEN_SHIELD: return 27; break;
   ITEM_TYPE_SILVER_SHIELD: return 28; break;
   ITEM_TYPE_GOLDEN_SHIELD: return 29; break;
   ITEM_TYPE_CLUB_SWORD: return 30; break;
   ITEM_TYPE_SILVER_SWORD: return 31; break;
   ITEM_TYPE_GOLDEN_SWORD: return 32; break;
   ITEM_TYPE_KNIFE: return 33; break;
   ITEM_TYPE_STONE_OF_DEFIANCE: return 24; break;
   ITEM_TYPE_NAUGHTY_LIST: return 25; break;
   ITEM_TYPE_KEY: return 26; break;
   }

   return 0;
}



