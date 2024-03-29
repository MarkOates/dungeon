


#include <dungeon/models/item_dialogue.hpp>

//#include <framework/objects/text_object.hpp>
//#include <framework/color.hpp>
//#include <framework/framework.hpp>
#include <cmath>

#include <AllegroFlare/Color.hpp>
#include <allegro5/allegro_primitives.h>
#include <dungeon/models/text_object.hpp>


ItemDialogue::ItemDialogue(float x, float y, float w, float h, ALLEGRO_BITMAP *item_bitmap, ALLEGRO_FONT *font, std::vector<std::string> pages)
   : place(x, y, w, h)
   , bitmap(item_bitmap)
   , font(font)
   , pages(pages)
   , showing_continue_notification(false)
{
   bitmap.align(0.5, 0.5);
   bitmap.position(150/2-30, 150/2-40);
   bitmap.rotation(-0.3);
   bitmap.scale(3.3, 3.3);
}



void ItemDialogue::draw(int page_num)
{
   place.start_transform();

   // draw the background and frame
   float padding_x = 40, padding_y = 40;
   al_draw_filled_rectangle(0-padding_x, 0-padding_y, place.size.x+padding_x, place.size.y+padding_y, AllegroFlare::color::black);
   al_draw_rectangle(0-padding_x, 0-padding_y, place.size.x+padding_x, place.size.y+padding_y, AllegroFlare::color::white, 5.0);

   // draw the item
   bitmap.draw();

   // draw the text
   if (font && page_num >= 0 && page_num < get_num_pages())
      al_draw_multiline_text(
            font,
            AllegroFlare::color::white,
            150,
            0,
            place.size.x - 150,
            al_get_font_line_height(font),
            0,
            pages[page_num].c_str()
         );

   // show the "continue" notification
   if (showing_continue_notification)
   {
      TextObject continue_notification("press ENTER to continue");
      continue_notification.font(font);
      continue_notification.position(place.size.x, place.size.y + 30);
      continue_notification.align(1.0, 1.0);
      continue_notification.scale(0.80, 0.80);
      //continue_notification.color(AllegroFlare::color::yellow); // COLOR
      //float notification_opacity = sin(al_get_time()*4.5) * 0.5 + 0.5; // NOTE: opacity was removed
      //continue_notification.opacity(notification_opacity);
      continue_notification.draw();
   }

   place.restore_transform();
}



int ItemDialogue::get_num_pages()
{
   return pages.size();
}



void ItemDialogue::set_showing_continue_notification()
{
   showing_continue_notification = true;
}



