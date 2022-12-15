#pragma once


//#include <framework/objects/bitmap_object.hpp>
#include <vector>
#include <string>
#include <AllegroFlare/Placement2D.hpp>
#include <dungeon/models/bitmap_object.hpp>


class ItemDialogue
{
private:
   AllegroFlare::Placement2D place;
   std::vector<std::string> pages;
   ALLEGRO_FONT *font;
   BitmapObject bitmap;
   bool showing_continue_notification;

public:
   ItemDialogue(float x, float y, float w, float h, ALLEGRO_BITMAP *item_bitmap, ALLEGRO_FONT *font, std::vector<std::string> pages);

   void draw(int page_num);
   int get_num_pages();
   void set_showing_continue_notification();
};


