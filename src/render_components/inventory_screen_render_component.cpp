

#include <render_components/inventory_screen_render_component.hpp>

#include <allegro5/allegro_primitives.h>
#include <framework/display.hpp>
#include <framework/color.hpp>
#include <models/inventory_screen.hpp>
#include <item_type_nums.hpp>



InventoryScreenRenderComponent::InventoryScreenRenderComponent(InventoryScreen *inventory_screen, Display *display)
   : inventory_screen(inventory_screen)
   , display(display)
   , fonts()
   , title(TextObject("Inventory"))
   , item_render_components()
{
   ALLEGRO_FONT *font = fonts["ChronoTrigger.ttf 60"];

   title.font(font)
      .align(0.5, 1.1)
      .scale(1, 1)
      .position(display->center(), display->middle()-200);

   int spacing = 150;
   float row_y = 270;
   float row_spacing = 150;
   int center = display->width() / 2;
   //int top_row = display->height() / 6 * 3;
   //int bottom_row = display->height() / 6 * 4;

   item_render_components.push_back(new InventoryItemRenderComponent(ITEM_TYPE_CLUB, center + spacing*-3, row_y));
   item_render_components.push_back(new InventoryItemRenderComponent(ITEM_TYPE_CLUB, center + spacing*-2, row_y));
   item_render_components.push_back(new InventoryItemRenderComponent(ITEM_TYPE_STONE_OF_DEFIANCE, center + spacing*-1, row_y));
   item_render_components.push_back(new InventoryItemRenderComponent(ITEM_TYPE_NAUGHTY_LIST, center + spacing*+0, row_y));
   item_render_components.push_back(new InventoryItemRenderComponent(ITEM_TYPE_SILVER_SHIELD, center + spacing*+1, row_y));
   item_render_components.push_back(new InventoryItemRenderComponent(ITEM_TYPE_GOLDEN_SHIELD, center + spacing*+2, row_y));
   item_render_components.push_back(new InventoryItemRenderComponent(ITEM_TYPE_NONE, center + spacing*+3, row_y));

   row_y += row_spacing;
   item_render_components.push_back(new InventoryItemRenderComponent(ITEM_TYPE_CLUB, center + spacing*-3, row_y));
   item_render_components.push_back(new InventoryItemRenderComponent(ITEM_TYPE_SILVER_SWORD, center + spacing*-2, row_y));
   item_render_components.push_back(new InventoryItemRenderComponent(ITEM_TYPE_GOLDEN_SWORD, center + spacing*-1, row_y));
   item_render_components.push_back(new InventoryItemRenderComponent(ITEM_TYPE_KEY, center + spacing*+0, row_y));
   item_render_components.push_back(new InventoryItemRenderComponent(ITEM_TYPE_NONE, center + spacing*+1, row_y));
   item_render_components.push_back(new InventoryItemRenderComponent(ITEM_TYPE_NONE, center + spacing*+2, row_y));
   item_render_components.push_back(new InventoryItemRenderComponent(ITEM_TYPE_NONE, center + spacing*+3, row_y));

   row_y += row_spacing;
   item_render_components.push_back(new InventoryItemRenderComponent(ITEM_TYPE_CLUB, center + spacing*-3, row_y));
   item_render_components.push_back(new InventoryItemRenderComponent(ITEM_TYPE_SILVER_SWORD, center + spacing*-2, row_y));
   item_render_components.push_back(new InventoryItemRenderComponent(ITEM_TYPE_GOLDEN_SWORD, center + spacing*-1, row_y));
   item_render_components.push_back(new InventoryItemRenderComponent(ITEM_TYPE_KEY, center + spacing*+0, row_y));
   item_render_components.push_back(new InventoryItemRenderComponent(ITEM_TYPE_NONE, center + spacing*+1, row_y));
   item_render_components.push_back(new InventoryItemRenderComponent(ITEM_TYPE_NONE, center + spacing*+2, row_y));
   item_render_components.push_back(new InventoryItemRenderComponent(ITEM_TYPE_NONE, center + spacing*+3, row_y));
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
   if (!display) throw std::runtime_error("InventoryScreenRenderComponent::draw(): cannot draw() on a nullptr display");

   float padding = 40;
   al_draw_filled_rectangle(padding, padding, display->width()-padding, display->height()-padding, color::black);
   title.draw();

   for (auto &item_render_component : item_render_components) item_render_component->draw();
}


