


#include <dungeon/factories/dialogue_factory.hpp>

#include <dungeon/models/item_dialogue.hpp>
#include <dungeon/item_type_nums.hpp>
//#include <framework/framework.hpp>



DialogueFactory::DialogueFactory(AllegroFlare::FontBin *font_bin, ALLEGRO_BITMAP *sprites_grid_bitmap)
   : item_sprite_sheet(sprites_grid_bitmap, SPRITES_GRID_SPRITE_WIDTH, SPRITES_GRID_SPRITE_HEIGHT, SPRITES_GRID_SPRITE_SCALING)
   //: item_sprite_sheet(SPRITES_GRID_FILENAME, SPRITES_GRID_SPRITE_WIDTH, SPRITES_GRID_SPRITE_HEIGHT, SPRITES_GRID_SPRITE_SCALING)
   , dialogue_font(nullptr)
{
   if (!font_bin) throw std::runtime_error("DialogueFactory no font_bin");
   dialogue_font = font_bin->auto_get("ChronoTrigger.ttf 50");
}



DialogueFactory::~DialogueFactory()
{
}



void DialogueFactory::init(AllegroFlare::FontBin *font_bin, ALLEGRO_BITMAP *sprites_grid_bitmap)
{
   if (!instance)
   {
      instance = new DialogueFactory(font_bin, sprites_grid_bitmap);
      initialized = true;
   }
   return;
}



DialogueFactory *DialogueFactory::get_instance()
{
   if (!initialized) throw std::runtime_error("DialogueFactory::get_instance not initialized");
   return instance;
}



ItemDialogue DialogueFactory::build_collected_item_dialog(int item_type)
{
   if (!initialized) throw std::runtime_error("DialogueFactory::build_collected_item_dialog not initialized");

   ALLEGRO_DISPLAY *display = al_get_current_display();
   int dialogue_x = al_get_display_width(display)/2;
   int dialogue_y = al_get_display_height(display)/4;
   int dialogue_w = 800;
   int dialogue_h = 160;
   ALLEGRO_FONT *font = get_instance()->dialogue_font;
   ALLEGRO_BITMAP *item_bitmap = nullptr;
   std::vector<std::string> dialogue;

   switch (item_type)
   {
   case ITEM_TYPE_CLUB:
      item_bitmap = get_instance()->item_sprite_sheet.get_sprite(23);
      dialogue = {"You found a Club!\n\nUse it to bash those naughty kids to their senses!"};
      break;
   case ITEM_TYPE_STONE_OF_DEFIANCE:
      item_bitmap = get_instance()->item_sprite_sheet.get_sprite(24);
      dialogue = {"You found the Stone of Defiance!\n\nNow you can see who has been nice, and who has been naughty."};
      break;
   case ITEM_TYPE_NAUGHTY_LIST:
      item_bitmap = get_instance()->item_sprite_sheet.get_sprite(25);
      dialogue = {"You found the Naughty List!\n\nNow you know how many naughty children are left to be punished."};
      break;
   case ITEM_TYPE_KEY:
      item_bitmap = get_instance()->item_sprite_sheet.get_sprite(26);
      dialogue = {"You found a Key!\n\nUnlock blocked areas and regain access to your lair!"};
      break;
   default:
      break;
   }

   ItemDialogue item_dialogue = ItemDialogue(dialogue_x, dialogue_y, dialogue_w, dialogue_h, item_bitmap, font, dialogue);

   return item_dialogue;
}



ItemDialogue DialogueFactory::build_dialogue(std::string message)
{
   if (!initialized) throw std::runtime_error("DialogueFactory::build_dialog not initialized");

   ALLEGRO_DISPLAY *display = al_get_current_display();
   int dialogue_x = al_get_display_width(display)/2;
   int dialogue_y = al_get_display_height(display)/4;
   int dialogue_w = 800;
   int dialogue_h = 160;
   ALLEGRO_FONT *font = get_instance()->dialogue_font;
   ALLEGRO_BITMAP *item_bitmap = nullptr;
   std::vector<std::string> dialogue = {message};

   ItemDialogue item_dialogue = ItemDialogue(dialogue_x, dialogue_y, dialogue_w, dialogue_h, item_bitmap, font, dialogue);

   return item_dialogue;
}



DialogueFactory *DialogueFactory::instance = nullptr;
bool DialogueFactory::initialized = false;



