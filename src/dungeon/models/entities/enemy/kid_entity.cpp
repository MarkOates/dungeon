


#include <dungeon/models/entities/enemy/kid_entity.hpp>

#include <dungeon/emitters/user_event_emitter.hpp>
#include <dungeon/motion_fx_type_names.hpp>
#include <dungeon/music_track_nums.hpp>
#include <dungeon/user_events.hpp>
#include <cmath>

#include <AllegroFlare/Color.hpp>
#include <AllegroFlare/Interpolators.hpp>
#include <AllegroFlare/EventEmitter.hpp>


#define IDENTITY_REVEAL_MAX 999.9



KidEntity::KidEntity(ElementID *parent, AllegroFlare::EventEmitter *event_emitter, SpriteSheet *sprite_sheet, AllegroFlare::Shader *flat_color_shader, float x, float y, std::string name, behavior_t behavior, int sprite_index, int identity_sprite_index)
   : Enemy::Base(parent, "kid", x, y)
   , name(name)
   , walk_speed(1.5)
   , state(STATE_STANDING_STILL)
   , flat_color_shader(flat_color_shader)
   , behavior(behavior)
   , event_emitter(event_emitter)
   , identity_reveal_counter(IDENTITY_REVEAL_MAX)
   , kid_bitmap(sprite_sheet->get_sprite(sprite_index))
   , identity_bitmap(sprite_sheet->get_sprite(identity_sprite_index))
   , health(1)
{
   if (!event_emitter) throw std::runtime_error("KidEntity:: no event emitter");

   place.size = { 60, 30 };

   if (sprite_index < 0) sprite_index = random.get_random_int(0, 16);
   bitmap.bitmap(kid_bitmap);
   bitmap.align(0.5, 1.0);
   bitmap.scale(2.0, 2.0);

   set("bound_in_world");
}



KidEntity::~KidEntity()
{
}



void KidEntity::reveal_behavior()
{
   identity_reveal_counter = 0.0;
}



void KidEntity::update()
{
   if (identity_reveal_counter < IDENTITY_REVEAL_MAX)
      identity_reveal_counter += 1.0 / 60.0;

   place += velocity;

   switch(state)
   {
   case STATE_TAKING_HIT:
      break;
   default:
      break;
   }
}



void KidEntity::draw()
{
   ALLEGRO_COLOR identity_color = get_identity_color();
   float tint_intensity = get_identity_tint_intensity();

   //flat_color_shader->use();
   flat_color_shader->activate();

   flat_color_shader->set_vec3("tint", identity_color.r, identity_color.g, identity_color.b);
   flat_color_shader->set_float("tint_intensity", tint_intensity);

   place.start_transform();
   bitmap.position(place.size.x/2, place.size.y/2);
      //bitmap.opacity(1.0);
      bitmap.bitmap(kid_bitmap);
      bitmap.draw();

   //flat_color_shader->stop();
   flat_color_shader->deactivate();

   bitmap.bitmap(identity_bitmap);
      //bitmap.opacity(tint_intensity); // HERE: tint intensity should be here?
      bitmap.draw();

   place.restore_transform();

}



void KidEntity::stand_still()
{
   set_state(STATE_STANDING_STILL);
}



void KidEntity::walk_up()
{
   set_state(STATE_WALKING_UP);
}



void KidEntity::walk_down()
{
   set_state(STATE_WALKING_DOWN);
}



void KidEntity::walk_left()
{
   set_state(STATE_WALKING_UP);
}



void KidEntity::walk_right()
{
   set_state(STATE_WALKING_RIGHT);
}



void KidEntity::take_hit()
{
   set_state(STATE_TAKING_HIT);
}



void KidEntity::set_state(state_t new_state)
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
      flag_for_deletion();
      //reveal_behavior();
      break;
   }
}



ALLEGRO_COLOR KidEntity::get_identity_color()
{
   ALLEGRO_COLOR identity_color;

   switch(behavior)
   {
   case BEHAVIOR_ADULT:
      identity_color = AllegroFlare::color::gray;
      break;
   case BEHAVIOR_NAUGHTY:
      identity_color = AllegroFlare::color::firebrick;
      break;
   case BEHAVIOR_NICE:
      identity_color = AllegroFlare::color::white;
      break;
   }

   return identity_color;
}



float KidEntity::get_identity_tint_intensity()
{
   float strobe_speed = 3.0;
   float identiy_reveal_duration = 4.0;

   switch (behavior)
   {
   case BEHAVIOR_ADULT:
      return 1.0 - std::min(identity_reveal_counter*(1.0/identiy_reveal_duration), 1.0);
      break;
   case BEHAVIOR_NAUGHTY:
      strobe_speed = 3.0;
      break;
   case BEHAVIOR_NICE:
      strobe_speed = 1.0;
      break;
   }

   float normalized_oscilation = sin(al_get_time() * strobe_speed*4) * 0.5 + 0.5;
   float tint_intensity = 1.0 - std::min(identity_reveal_counter*(1.0/identiy_reveal_duration), 1.0);

   return normalized_oscilation * AllegroFlare::interpolator::fast_in(tint_intensity);
}



std::string KidEntity::get_name()
{
   return name;
}



