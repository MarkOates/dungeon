
#include <gtest/gtest.h>

#include <DungeonPlus/Animation.hpp>
#include <allegro5/allegro_image.h>


TEST(DungeonPlus_AnimationTest, can_be_created_without_blowing_up)
{
   DungeonPlus::Animation animation;
}


TEST(DungeonPlus_AnimationTest, dev_test)
{
   al_init();
   al_init_image_addon();
   ALLEGRO_DISPLAY *display = al_create_display(1920, 1080);

   ALLEGRO_BITMAP *sprite_sheet_bitmap = al_load_bitmap("./bin/data/bitmaps/sprites_grid-x.png");

   SpriteSheet sprite_sheet(sprite_sheet_bitmap); // auto-inits

   //al_rest(2);

   al_destroy_display(display);
   al_shutdown_image_addon();
   al_uninstall_system();
}


