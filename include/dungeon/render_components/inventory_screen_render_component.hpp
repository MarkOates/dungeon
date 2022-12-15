#pragma once


//#include <framework/objects/text_object.hpp>
#include <dungeon/render_components/inventory_item_render_component.hpp>
#include <dungeon/models/text_object.hpp>
#include <AllegroFlare/FontBin.hpp>


class InventoryScreen;
//class Display;


class InventoryScreenRenderComponent
{
private:
   InventoryScreen *inventory_screen;
   //Display *display;
   //AllegroFlare::FontBin fonts;
   AllegroFlare::FontBin *font_bin;
   ALLEGRO_BITMAP *sprites_grid_bitmap;
   TextObject title;
   std::vector<InventoryItemRenderComponent *> item_render_components;

public:
   InventoryScreenRenderComponent(AllegroFlare::FontBin *font_bin, ALLEGRO_BITMAP *sprites_grid_bitmap, InventoryScreen *inventory_screen);
   ~InventoryScreenRenderComponent();

   void hilight(int index);
   void select(int index);

   void draw();
};


