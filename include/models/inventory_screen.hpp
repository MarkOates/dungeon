#pragma once


#include <framework/motion.hpp>
#include <render_components/inventory_screen_render_component.hpp>


class Inventory;
class Display;


#define INVENTORY_SCREEN__SHOW ALLEGRO_GET_EVENT_TYPE('N','v','S','h')
#define INVENTORY_SCREEN__HIDE ALLEGRO_GET_EVENT_TYPE('N','v','S','h')
#define INVENTORY_SCREEN__MOVE_CURSOR_UP ALLEGRO_GET_EVENT_TYPE('N','v','C','U')
#define INVENTORY_SCREEN__MOVE_CURSOR_DOWN ALLEGRO_GET_EVENT_TYPE('N','v','C','D')
#define INVENTORY_SCREEN__MOVE_CURSOR_LEFT ALLEGRO_GET_EVENT_TYPE('N','v','C','L')
#define INVENTORY_SCREEN__MOVE_CURSOR_RIGHT ALLEGRO_GET_EVENT_TYPE('N','v','C','R')
#define INVENTORY_SCREEN__SELECT_ITEM ALLEGRO_GET_EVENT_TYPE('N','v','S','I')


class InventoryScreen // (not actually a "Screen" in the framework sense)
{
private:
   Inventory *inventory;
   Motion motion;
   float display_counter;
   int rows, columns;
   int cursor;
   int selector;
   Display *display;
   FontBin fonts;
   TextObject title;
   std::vector<InventoryItemRenderComponent *> item_render_components;
   //InventoryScreenRenderComponent inventory_screen_render_component;

   int get_num_items();

public:
   InventoryScreen(Inventory *inventory, Display *display);
   ~InventoryScreen();

   int get_selected_item();

   void show();
   void hide();
   void move_cursor_up();
   void move_cursor_down();
   void move_cursor_left();
   void move_cursor_right();
   void select_item_at_cursor();

   void hilight(int index);
   void select(int index);

   void update(float time_now);
   void draw(Display *display);
};


