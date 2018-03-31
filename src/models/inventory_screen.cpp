


#include <framework/display.hpp>
#include <emitters/user_event_emitter.hpp>
#include <models/inventory.hpp>
#include <models/inventory_screen.hpp>
#include <render_components/inventory_screen_render_component.hpp>
#include <music_track_nums.hpp>
#include <user_events.hpp>



InventoryScreen::InventoryScreen(Inventory *inventory, Display *display)
   : inventory(inventory)
   , motion()
   , display_counter(0)
   , rows(3)
   , columns(7)
   , cursor(0)
   , selector(0)
   //, inventory_screen_render_component(this, display)
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



InventoryScreen::~InventoryScreen()
{
   for (auto &item_render_component : item_render_components) delete item_render_component;
}



void InventoryScreen::hilight(int index)
{
   for (unsigned i=0; i<item_render_components.size(); i++)
   {
      InventoryItemRenderComponent &item_render_component = *item_render_components[i];
      if (i == index) item_render_component.hilight();
      else item_render_component.unhilight();
   }
}


void InventoryScreen::select(int index)
{
   for (unsigned i=0; i<item_render_components.size(); i++)
   {
      InventoryItemRenderComponent &item_render_component = *item_render_components[i];
      if (i == index) item_render_component.select();
      else item_render_component.unselect();
   }
}


int InventoryScreen::get_num_items()
{
   return rows * columns;
}



int InventoryScreen::get_selected_item()
{
   if (!inventory) throw std::runtime_error("InventoryScreen: cannot get_selected_item() with a nullptr inventory");
   return inventory->get_ordered_item(selector);
}



void InventoryScreen::show()
{
   UserEventEmitter::emit_event(PLAY_SOUND_EFFECT, 0, (intptr_t)(new std::string(FAIL_MOAN_SOUND_EFFECT)));
   motion.cmove_to(&display_counter, 1.0, 1.0);
}



void InventoryScreen::hide()
{
   motion.cmove_to(&display_counter, 0.0, 1.0);
}



void InventoryScreen::move_cursor_up()
{
   cursor = (cursor - columns + get_num_items()) % get_num_items();
   hilight(cursor);
}



void InventoryScreen::move_cursor_down()
{
   cursor = (cursor + columns) % get_num_items();
   hilight(cursor);
}



void InventoryScreen::move_cursor_left()
{
   cursor = (cursor - 1 + get_num_items()) % get_num_items();
   hilight(cursor);
}



void InventoryScreen::move_cursor_right()
{
   cursor = (cursor + 1 + get_num_items()) % get_num_items();
   hilight(cursor);
}



void InventoryScreen::select_item_at_cursor()
{
   selector = cursor;
   //inventory_screen_render_component.select(selector);
   select(selector);
   UserEventEmitter::emit_event(PLAY_SOUND_EFFECT, 0, (intptr_t)(new std::string(SWORD_SCHLING_SOUND_EFFECT)));
   UserEventEmitter::emit_event(INVENTORY_EQUIP_WEAPON, item_render_components[selector]->get_item_type());
}



void InventoryScreen::update(float time_now)
{
   motion.update(time_now);
}



void InventoryScreen::draw(Display *display)
{
   if (!display) throw std::runtime_error("InventoryScreen::draw(): cannot draw() on a nullptr display");

   float padding = 40;
   al_draw_filled_rectangle(padding, padding, display->width()-padding, display->height()-padding, color::black);
   title.draw();

   for (auto &item_render_component : item_render_components) item_render_component->draw();
   //inventory_screen_render_component.draw();
}



