#pragma once


#include <dungeon/models/item_dialogue.hpp>
#include <dungeon/models/sprite_sheet.hpp>
#include <AllegroFlare/FontBin.hpp>


class DialogueFactory
{
private:
   DialogueFactory(AllegroFlare::FontBin *font_bin, ALLEGRO_BITMAP *sprites_grid_bitmap);
   ~DialogueFactory();
   SpriteSheet item_sprite_sheet;
   ALLEGRO_FONT *dialogue_font;
   static DialogueFactory *instance;
   static DialogueFactory *get_instance();
   static bool initialized;

public:

   static void init(AllegroFlare::FontBin *font_bin, ALLEGRO_BITMAP *sprites_grid_bitmap);

   static ItemDialogue build_collected_item_dialog(int item_type);
   static ItemDialogue build_dialogue(std::string message);
};


