#pragma once


//#include <framework/objects/bitmap_object.hpp>
//#include <framework/placement2d.hpp>
#include <dungeon/models/sprite_sheet.hpp>
#include <dungeon/item_type_nums.hpp>
#include <dungeon/models/bitmap_object.hpp>
#include <AllegroFlare/Placement2D.hpp>


class InventoryItemRenderComponent
{
private:
   int item_type;
   float inventory_screen_position_x, inventory_screen_position_y;
   AllegroFlare::Placement2D place;
   int count;
   SpriteSheet sprite_sheet;
   BitmapObject bitmap;
   int selected;
   int hilighted;

public:
   InventoryItemRenderComponent(item_t item_type, ALLEGRO_BITMAP *sprites_grid_bitmap, float inventory_screen_position_x, float inventory_screen_position_y);
   ~InventoryItemRenderComponent();

   int get_item_type();

   void select();
   void hilight();
   void unselect();
   void unhilight();

   void draw();
};


