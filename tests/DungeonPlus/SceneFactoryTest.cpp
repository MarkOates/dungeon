
#include <gtest/gtest.h>
#include <DungeonPlus/Testing/TestHelper.hpp>

#include <DungeonPlus/SceneFactory.hpp>

#include <allegro5/allegro_image.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_font.h>

#include <AllegroFlare/UsefulPHP.hpp>


TEST(DungeonPlus_SceneFactoryTest, can_be_created_without_blowing_up)
{
   DungeonPlus::SceneFactory scene_factory;
}


TEST(DungeonPlus_SceneFactoryTest, create_scene_0__will_create_the_scene)
{
   al_init();
   al_init_image_addon();
   al_init_font_addon();
   al_init_ttf_addon();

   ALLEGRO_DISPLAY *display = al_create_display(1920, 1080);
   ALLEGRO_BITMAP *sprite_sheet_bitmap = al_load_bitmap("./bin/data/bitmaps/sprites_grid-x.png");
   ALLEGRO_FONT *font = al_load_font("./bin/data/fonts/ChronoTrigger.ttf", -50, 0);
   SpriteSheet sprite_sheet(sprite_sheet_bitmap, 48, 48, 8); // auto-inits
   al_destroy_bitmap(sprite_sheet_bitmap);

   //DungeonPlus::AnimationBook animation_book;
   //animation_book.init();
   //AllegroFlare::EventEmitter event_emitter;
   //AllegroFlare::Shader *flat_color_shader = new AllegroFlare::Shader(
         //AllegroFlare::php::file_get_contents("./bin/data/shaders/flat_color_shader.vertex.glsl"),
         //AllegroFlare::php::file_get_contents("./bin/data/shaders/flat_color_shader.fragment.glsl")
      //);
   //flat_color_shader->initialize();

   //DungeonPlus::SceneFactory scene_factory(&animation_book, &event_emitter, flat_color_shader);
   //scene_factory.initialize();
   //DungeonPlus::Scene *scene = scene_factory.create_scene_0();
   
   int frames = 120;
   for (int i=0; i<frames; i++)
   {
      al_clear_to_color(ALLEGRO_COLOR{0, 0, 0, 1});

      //scene->update();
      //scene->draw();

      al_flip_display(); // assumes a rest of 1/60.0f
   }


   //delete flat_color_shader;
   al_destroy_font(font);
   sprite_sheet.destroy();
   al_destroy_display(display);
   al_shutdown_font_addon();
   al_shutdown_ttf_addon();
   al_shutdown_image_addon();
   al_uninstall_system();
}


