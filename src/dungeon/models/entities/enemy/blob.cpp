


#include <dungeon/models/entities/enemy/blob.hpp>

#include <dungeon/emitters/user_event_emitter.hpp>
#include <dungeon/motion_fx_type_names.hpp>
#include <dungeon/music_track_nums.hpp>
#include <dungeon/user_events.hpp>
#include <cmath>

#include <AllegroFlare/Color.hpp>
#include <AllegroFlare/Interpolators.hpp>
#include <AllegroFlare/EventEmitter.hpp>


#define HURT_REVEAL_MAX 999.9



Blob::Blob(
      ElementID *parent,
      AllegroFlare::EventEmitter *event_emitter,
      SpriteSheet *sprite_sheet,
      AllegroFlare::Shader *flat_color_shader,
      float x,
      float y,
      std::string name
   )
   : Enemy::Base(parent, "blob", x, y)
   , name(name)
   , walk_speed(1.5)
   , state(STATE_STANDING_STILL)
   , flat_color_shader(flat_color_shader)
   , event_emitter(event_emitter)
   , hurt_reveal_counter(HURT_REVEAL_MAX)
   , sprite_sheet(sprite_sheet)
   , health(1)
{
   if (!event_emitter) throw std::runtime_error("Blob:: no event emitter");

   place.size = { 60, 30 };

   //if (sprite_index < 0) sprite_index = random.get_random_int(0, 16);
   //bitmap.opacity(1.0);
   bitmap.bitmap(sprite_sheet->get_cell(6));
   bitmap.align(0.5, 1.0);
   bitmap.scale(2.0, 2.0);

   set("bound_in_world");
}



Blob::~Blob()
{
}



void Blob::reveal_hurt()
{
   hurt_reveal_counter = 0.0;
}



void Blob::stand_still()
{
   set_state(STATE_STANDING_STILL);
}



void Blob::walk_up()
{
   set_state(STATE_WALKING_UP);
}



void Blob::walk_down()
{
   set_state(STATE_WALKING_DOWN);
}



void Blob::walk_left()
{
   set_state(STATE_WALKING_UP);
}



void Blob::walk_right()
{
   set_state(STATE_WALKING_RIGHT);
}



void Blob::take_hit()
{
   set_state(STATE_TAKING_HIT);
}



void Blob::set_state(state_t new_state)
{
   state = new_state;

   switch (state)
   {
   case STATE_STANDING_STILL:
      velocity.position = { 0.0, 0.0 };
      break;
   case STATE_WALKING_UP:
      velocity.position = { 0.0, (float)-walk_speed/2 };
      break;
   case STATE_WALKING_DOWN:
      velocity.position = { 0.0, (float)walk_speed/2 };
      break;
   case STATE_WALKING_LEFT:
      velocity.position = { (float)-walk_speed, 0.0 };
      break;
   case STATE_WALKING_RIGHT:
      velocity.position = { (float)walk_speed, 0.0 };
      break;
   case STATE_TAKING_HIT:
      velocity.position = { 0.0, 0.0 };
      event_emitter->emit_event(PLAY_SOUND_EFFECT, HURT_SOUND_EFFECT);
      event_emitter->emit_event(SPAWN_MOTION_FX, (intptr_t)(new std::string(MOTION_FX_SLASH_POOF)), place.position.x + place.size.x/2, place.position.y + place.size.y/2);
      //flag_for_deletion();
      reveal_hurt();
      break;
   }
}


void Blob::update()
{
   if (hurt_reveal_counter < HURT_REVEAL_MAX) hurt_reveal_counter += 1.0 / 60.0;

   place += velocity;
}



void Blob::draw()
{
   ALLEGRO_COLOR hurt_color = get_hurt_color();
   float tint_intensity = get_hurt_tint_intensity();

   flat_color_shader->activate();

   flat_color_shader->set_vec3("tint", hurt_color.r, hurt_color.g, hurt_color.b);
   flat_color_shader->set_float("tint_intensity", tint_intensity);

   place.start_transform();
   //al_draw_bitmap(sprite_sheet->get_cell(0), 0, 0, 0);
   bitmap.position(place.size.x/2, place.size.y/2);
      //bitmap.opacity(1.0);
      bitmap.bitmap(sprite_sheet->get_cell(0));
      bitmap.draw();

   flat_color_shader->deactivate();
   //place.draw_box(ALLEGRO_COLOR{0.1, 0.3, 0.95, 1.0}, true);
      //void draw_box_with_padding(ALLEGRO_COLOR color, bool draw_origin, float pt, float pr, float pb, float pl);
      //oid draw_origin();

   place.restore_transform();
   place.draw_box(ALLEGRO_COLOR{0.85, 0.9, 0.24, 1.0}, true);
}



ALLEGRO_COLOR Blob::get_hurt_color()
{
   ALLEGRO_COLOR hurt_color;
   hurt_color = AllegroFlare::color::firebrick;
   return hurt_color;
}



float Blob::get_hurt_tint_intensity()
{
   float strobe_speed = 3.0;
   float identiy_reveal_duration = 4.0;

   float normalized_oscilation = sin(al_get_time() * strobe_speed*4) * 0.5 + 0.5;
   float tint_intensity = 1.0 - std::min(hurt_reveal_counter*(1.0/identiy_reveal_duration), 1.0);

   return normalized_oscilation * AllegroFlare::interpolator::fast_in(tint_intensity);
}



std::string Blob::get_name()
{
   return name;
}



