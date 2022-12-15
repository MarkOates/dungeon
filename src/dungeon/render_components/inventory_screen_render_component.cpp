

#include <dungeon/render_components/inventory_screen_render_component.hpp>

#include <allegro5/allegro_primitives.h>
//#include <framework/display.hpp>
//#include <framework/color.hpp>
#include <dungeon/models/inventory_screen.hpp>
#include <dungeon/item_type_nums.hpp>
#include <AllegroFlare/Color.hpp>



InventoryScreenRenderComponent::InventoryScreenRenderComponent(AllegroFlare::FontBin *font_bin, ALLEGRO_BITMAP *sprites_grid_bitmap, InventoryScreen *inventory_screen)
   : inventory_screen(inventory_screen)
   //, display(display)
   //, fonts()
   , font_bin(font_bin)
   , title(TextObject("Inventory"))
   , item_render_components()
   , sprites_grid_bitmap(sprites_grid_bitmap)
   //, font_bin(font_bin)
{
   if (!font_bin) throw std::runtime_error("InventoryItemRenderComponent:: font_bin missing");
   if (!sprites_grid_bitmap) throw std::runtime_error("InventoryItemRenderComponent:: sprites_grid_bitmap missing");

   ALLEGRO_FONT *font = font_bin->auto_get("ChronoTrigger.ttf 60");

   title.font(font)
      .align(0.5, 1.1)
      .scale(1, 1)
      .position(1920/2, 1080/2-200);

   int spacing = 150;
   float row_y = 270;
   float row_spacing = 150;
   int center = 1920 / 2;
   //int top_row = display->height() / 6 * 3;
   //int bottom_row = display->height() / 6 * 4;

   item_render_components.push_back(new InventoryItemRenderComponent(ITEM_TYPE_CLUB, sprites_grid_bitmap, center + spacing*-3, row_y));
   item_render_components.push_back(new InventoryItemRenderComponent(ITEM_TYPE_CLUB, sprites_grid_bitmap, center + spacing*-2, row_y));
   item_render_components.push_back(new InventoryItemRenderComponent(ITEM_TYPE_STONE_OF_DEFIANCE, sprites_grid_bitmap, center + spacing*-1, row_y));
   item_render_components.push_back(new InventoryItemRenderComponent(ITEM_TYPE_NAUGHTY_LIST, sprites_grid_bitmap, center + spacing*+0, row_y));
   item_render_components.push_back(new InventoryItemRenderComponent(ITEM_TYPE_SILVER_SHIELD, sprites_grid_bitmap, center + spacing*+1, row_y));
   item_render_components.push_back(new InventoryItemRenderComponent(ITEM_TYPE_GOLDEN_SHIELD, sprites_grid_bitmap, center + spacing*+2, row_y));
   item_render_components.push_back(new InventoryItemRenderComponent(ITEM_TYPE_NONE, sprites_grid_bitmap, center + spacing*+3, row_y));

   row_y += row_spacing;
   item_render_components.push_back(new InventoryItemRenderComponent(ITEM_TYPE_CLUB, sprites_grid_bitmap, center + spacing*-3, row_y));
   item_render_components.push_back(new InventoryItemRenderComponent(ITEM_TYPE_SILVER_SWORD, sprites_grid_bitmap, center + spacing*-2, row_y));
   item_render_components.push_back(new InventoryItemRenderComponent(ITEM_TYPE_GOLDEN_SWORD, sprites_grid_bitmap, center + spacing*-1, row_y));
   item_render_components.push_back(new InventoryItemRenderComponent(ITEM_TYPE_KEY, sprites_grid_bitmap, center + spacing*+0, row_y));
   item_render_components.push_back(new InventoryItemRenderComponent(ITEM_TYPE_NONE, sprites_grid_bitmap, center + spacing*+1, row_y));
   item_render_components.push_back(new InventoryItemRenderComponent(ITEM_TYPE_NONE, sprites_grid_bitmap, center + spacing*+2, row_y));
   item_render_components.push_back(new InventoryItemRenderComponent(ITEM_TYPE_NONE, sprites_grid_bitmap, center + spacing*+3, row_y));

   row_y += row_spacing;
   item_render_components.push_back(new InventoryItemRenderComponent(ITEM_TYPE_CLUB, sprites_grid_bitmap, center + spacing*-3, row_y));
   item_render_components.push_back(new InventoryItemRenderComponent(ITEM_TYPE_SILVER_SWORD, sprites_grid_bitmap, center + spacing*-2, row_y));
   item_render_components.push_back(new InventoryItemRenderComponent(ITEM_TYPE_GOLDEN_SWORD, sprites_grid_bitmap, center + spacing*-1, row_y));
   item_render_components.push_back(new InventoryItemRenderComponent(ITEM_TYPE_KEY, sprites_grid_bitmap, center + spacing*+0, row_y));
   item_render_components.push_back(new InventoryItemRenderComponent(ITEM_TYPE_NONE, sprites_grid_bitmap, center + spacing*+1, row_y));
   item_render_components.push_back(new InventoryItemRenderComponent(ITEM_TYPE_NONE, sprites_grid_bitmap, center + spacing*+2, row_y));
   item_render_components.push_back(new InventoryItemRenderComponent(ITEM_TYPE_NONE, sprites_grid_bitmap, center + spacing*+3, row_y));
}


InventoryScreenRenderComponent::~InventoryScreenRenderComponent()
{
   for (auto &item_render_component : item_render_components) delete item_render_component;
}


void InventoryScreenRenderComponent::hilight(int index)
{
   for (unsigned i=0; i<item_render_components.size(); i++)
   {
      InventoryItemRenderComponent &item_render_component = *item_render_components[i];
      if (i == index) item_render_component.hilight();
      else item_render_component.unhilight();
   }
}


void InventoryScreenRenderComponent::select(int index)
{
   for (unsigned i=0; i<item_render_components.size(); i++)
   {
      InventoryItemRenderComponent &item_render_component = *item_render_components[i];
      if (i == index) item_render_component.select();
      else item_render_component.unselect();
   }
}


void InventoryScreenRenderComponent::draw()
{
   if (!inventory_screen) throw std::runtime_error("InventoryScreenRenderComponent::draw(): cannot draw() on a nullptr inventory_screen");
   //if (!display) throw std::runtime_error("InventoryScreenRenderComponent::draw(): cannot draw() on a nullptr display");

   float padding = 40;
   al_draw_filled_rectangle(padding, padding, 1920/2-padding, 1080/2-padding, AllegroFlare::color::black);
   title.draw();

   for (auto &item_render_component : item_render_components) item_render_component->draw();
}


