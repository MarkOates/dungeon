
#include <gtest/gtest.h>

#include <DungeonPlus/AnimationBook.hpp>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_font.h>


TEST(DungeonPlus_AnimationBookTest, can_be_created_without_blowing_up)
{
   DungeonPlus::AnimationBook animation_book;
}


TEST(DungeonPlus_AnimationBookTest, DISABLED__VISUAL__will_load_an_animation)
{
   al_init();
   al_init_image_addon();
   al_init_font_addon();
   al_init_ttf_addon();
   ALLEGRO_DISPLAY *display = al_create_display(1920, 1080);
   ALLEGRO_FONT *font = al_load_font("./bin/data/fonts/ChronoTrigger.ttf", -50, 0);

   DungeonPlus::AnimationBook animation_book;
   animation_book.init();

   DungeonPlus::Animation animation = animation_book.get_animation_by_name("blob");
   
   int frames = 120;
   animation.start();
   for (int i=0; i<frames; i++)
   {
      al_clear_to_color(ALLEGRO_COLOR{0, 0, 0, 1});

      // update and draw
      animation.update();
      animation.draw();

      // draw info text
      uint32_t frame_id = animation.get_frame_id_at(0.21);
      al_draw_textf(font, ALLEGRO_COLOR{1, 1, 1, 1}, 10, 10, 0, "frame %d", frame_id);

      al_flip_display(); // assumes a rest of 1/60.0f
   }


   al_destroy_font(font);
   al_destroy_display(display);
   al_shutdown_font_addon();
   al_shutdown_ttf_addon();
   al_shutdown_image_addon();
   al_uninstall_system();
}


TEST(DungeonPlus_AnimationBookTest, contains_some_expected_content)
{
   al_init();
   al_init_image_addon();
   al_init_font_addon();
   al_init_ttf_addon();
   ALLEGRO_DISPLAY *display = al_create_display(1920, 1080);
   ALLEGRO_FONT *font = al_load_font("./bin/data/fonts/ChronoTrigger.ttf", -50, 0);

   DungeonPlus::AnimationBook animation_book;
   animation_book.init();

   DungeonPlus::Animation animation = animation_book.get_animation_by_name("blob");
   
   int frames = 120;
   animation.start();
   for (int i=0; i<frames; i++)
   {
      al_clear_to_color(ALLEGRO_COLOR{0, 0, 0, 1});

      // update and draw
      animation.update();
      animation.draw();

      // draw info text
      uint32_t frame_id = animation.get_frame_id_at(0.21);
      al_draw_textf(font, ALLEGRO_COLOR{1, 1, 1, 1}, 10, 10, 0, "frame %d", frame_id);

      al_flip_display(); // assumes a rest of 1/60.0f
   }


   al_destroy_font(font);
   al_destroy_display(display);
   al_shutdown_font_addon();
   al_shutdown_ttf_addon();
   al_shutdown_image_addon();
   al_uninstall_system();
}


