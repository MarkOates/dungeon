

#define ALLEGRO_UNSTABLE 1

#include <framework/screens/gamer_input_screen.hpp>
#include <framework/screen.hpp>
#include <dungeon/models/audio_controller.hpp>
#include <dungeon/emitters/user_event_emitter.hpp>
#include <dungeon/factories/storyboard_factory.hpp>
#include <dungeon/screens/title_screen.hpp>
#include <dungeon/screens/game_play_screen.hpp>
#include <dungeon/user_events.hpp>


#include <framework/bitmap.hpp>



#define SCREEN_W (16*16)
#define SCREEN_H (9*16)
#define SCREEN_S 10





bool debug_mode = false;






class E
{
public:
   SpriteSheet &sprite_sheet;
   placement2d placement;
   placement2d velocity;
   Bitmap bitmap;

   E(SpriteSheet &sprite_sheet, int sprite_index, float x, float y, float w, float h)
      : sprite_sheet(sprite_sheet)
      , placement(x, y, w, h)
      , velocity(0, 0, 0, 0, 0, 0, 0, 0, 0)
      , bitmap(sprite_sheet.get_sprite(sprite_index), 0, 0)
   {
      placement.align = vec2d(0.5, 0.5);
      bitmap.align = vec2d(0.5, 1.0);
      bitmap.position = vec2d(placement.w/2, placement.h/2);
   }
   ~E() {}

   void draw()
   {
      al_draw_filled_ellipse(placement.x, placement.y, 4, 2, color::black);
      placement.start_transform();
      bitmap.draw();
      if (debug_mode) al_draw_filled_rectangle(0, 0, placement.size.x, placement.size.y, color::color(color::orange, 0.3));
      placement.restore_transform();
      if (debug_mode) draw_crosshair(placement.x, placement.y, color::yellow);
   }
};




class Dungeon : public Screen
{
public:
   GamerInputScreen gamer_input_screen;
   ALLEGRO_BITMAP *unscaled_render;
   SpriteSheet sprite_sheet;
   E player, item, kid, bookshelf, chest;
   std::vector<E *> entities;
   Bitmap background;

   Dungeon(Display *display)
      : Screen(display)
      , unscaled_render(nullptr)
      , gamer_input_screen(display)
      , sprite_sheet(SPRITES_GRID_FILENAME, 48, 48)
      , player(sprite_sheet, (18), SCREEN_W/2, SCREEN_H/3*2, 16, 8)
      , item(sprite_sheet, (32), SCREEN_W/2, SCREEN_H/3*2, 16, 8)
      , kid(sprite_sheet, (17), SCREEN_W/2, SCREEN_H/3*2, 16, 8)
      , bookshelf(sprite_sheet, (44), SCREEN_W/2, SCREEN_H/3*2, 32, 8)
      , chest(sprite_sheet, (45), SCREEN_W/2, SCREEN_H/3*2, 32, 8)
      , background(Framework::bitmap("background-4-01.png"), 0, 0)
   {
      ALLEGRO_STATE previous_new_bitmap_state;
      al_store_state(&previous_new_bitmap_state, ALLEGRO_STATE_BITMAP);
      al_set_new_bitmap_flags(ALLEGRO_CONVERT_BITMAP);

      unscaled_render = al_create_bitmap(SCREEN_W, SCREEN_H);

      create_and_use_backbuffer_sub_bitmap_of(unscaled_render);

      al_restore_state(&previous_new_bitmap_state);

      std::vector<E *> elems = { &player, &item, &kid, &bookshelf, &chest };
      int position = 20;
      for (auto &elem : elems)
      {
         elem->placement.x = position;
         position += 48;
         entities.push_back(elem);
      }
      //player.rotation = 0.2;
   }

   void on_gamer_button_down(int button)
   {
      switch (button)
      {
      case GAMER_BUTTON_UP: player.velocity.y = -1.0; break;
      case GAMER_BUTTON_DOWN: player.velocity.y = 1.0; break;
      case GAMER_BUTTON_LEFT: player.velocity.x = -1.0; break;
      case GAMER_BUTTON_RIGHT: player.velocity.x = 1.0; break;
      }
   }

   void on_gamer_button_up(int button)
   {
      switch (button)
      {
      case GAMER_BUTTON_UP: player.velocity.y = 0; break;
      case GAMER_BUTTON_DOWN: player.velocity.y = 0; break;
      case GAMER_BUTTON_LEFT: player.velocity.x = 0; break;
      case GAMER_BUTTON_RIGHT: player.velocity.x = 0; break;
      }
   }

   void user_event_func() override
   {
      ALLEGRO_EVENT *event = Framework::current_event;
      switch (event->user.type)
      {
         case ALLEGRO_EVENT_GAMER_BUTTON_DOWN:
         {
            on_gamer_button_down(event->user.data1);
            break;
         }
         case ALLEGRO_EVENT_GAMER_BUTTON_UP:
         {
            on_gamer_button_up(event->user.data1);
            break;
         }
      }
   }

   void update()
   {
      for (auto &entity : entities)
         entity->placement.position += entity->velocity.position;
   }

   std::vector<E *> entities_y_sorted()
   {
      std::vector<E *> flat_list = entities;

      std::sort(flat_list.begin(), flat_list.end(),[](const E *a, const E *b)
            { return a->placement.position.y < b->placement.position.y; }
         );

      return flat_list;
   }

   void draw()
   {
      al_clear_to_color(color::gray);

      background.draw();

      for (auto &entity : entities_y_sorted())
         entity->draw();
   }

   void primary_timer_func() override
   {
      update();
      draw();

      ALLEGRO_STATE previous_drawing_surface;
      al_store_state(&previous_drawing_surface, ALLEGRO_STATE_TARGET_BITMAP);
      al_set_target_bitmap(al_get_backbuffer(display->al_display));
      al_draw_scaled_bitmap(unscaled_render, 0, 0, SCREEN_W, SCREEN_H, 0, 0, SCREEN_W*SCREEN_S, SCREEN_H*SCREEN_S, 0);

      al_restore_state(&previous_drawing_surface);
   }
};



int main(int argc, char **argv)
{
   Framework::initialize();
   Display *display = Framework::create_display(SCREEN_W*SCREEN_S, SCREEN_H*SCREEN_S, ALLEGRO_OPENGL | ALLEGRO_PROGRAMMABLE_PIPELINE);
   Dungeon *proj = new Dungeon(display);
   Framework::run_loop();
   return 0;
}




