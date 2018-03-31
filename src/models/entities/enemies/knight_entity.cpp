


#include <models/entities/enemies/knight_entity.hpp>

#include <emitters/user_event_emitter.hpp>
#include <factories/entity_factory.hpp>
#include <cmath>
#include <motion_fx_type_names.hpp>
#include <music_track_nums.hpp>
#include <user_events.hpp>



#define IDENTITY_REVEAL_MAX 999.9



KnightEntity::KnightEntity(ElementID *parent, SpriteSheet *sprite_sheet, Shader *flat_color_shader, float x, float y, std::string name, knight_behavior_t behavior, int sprite_index, int identity_sprite_index)
   : EnemyBase(parent, "knight", x, y)
   , sprite_sheet(sprite_sheet)
   , name(name)
   , walk_speed(1.5)
   , state(STATE_STANDING_STILL)
   , flat_color_shader(flat_color_shader)
   , behavior(behavior)
   , identity_reveal_counter(IDENTITY_REVEAL_MAX)
   , identity_bitmap(sprite_sheet->get_sprite(identity_sprite_index))
   , health(5)
{
   place.size = vec2d(60, 30);

   if (sprite_index < 0) sprite_index = random_int(0, 16);
   bitmap.bitmap(sprite_sheet->get_sprite(34));
   bitmap.align(0.5, 1.0);
   bitmap.scale(2.0, 2.0);
   bitmap.position(place.size.x/2, place.size.y/2);

   set("bound_in_world");
}



KnightEntity::~KnightEntity()
{
}



void KnightEntity::reveal_behavior()
{
   identity_reveal_counter = 0.0;
}



void KnightEntity::update()
{
   state_counter -= 1.0 / 60.0;

   if (identity_reveal_counter < IDENTITY_REVEAL_MAX)
      identity_reveal_counter += 1.0 / 60.0;

   place += velocity;

   switch(state)
   {
   case STATE_ATTACKING:
      if (state_counter <= 0)
      {
         bitmap.bitmap(sprite_sheet->get_sprite(34));
         set_state(STATE_STANDING_STILL);
      }
   case STATE_TAKING_HIT:
      break;
   default:
      break;
   }
}



void KnightEntity::draw()
{
   ALLEGRO_COLOR identity_color = get_identity_color();
   float tint_intensity = get_identity_tint_intensity();

   flat_color_shader->use();

   flat_color_shader->set_vec3("tint", identity_color.r, identity_color.g, identity_color.b);
   flat_color_shader->set_float("tint_intensity", tint_intensity);

   place.start_transform();
   bitmap.draw();

   flat_color_shader->stop();

   //bitmap.bitmap(identity_bitmap);
      //bitmap.opacity(tint_intensity);
      //bitmap.draw();

   place.restore_transform();

}



void KnightEntity::attack()
{
   set_state(STATE_ATTACKING);
}



void KnightEntity::stand_still()
{
   set_state(STATE_STANDING_STILL);
}



void KnightEntity::walk_up()
{
   set_state(STATE_WALKING_UP);
}



void KnightEntity::walk_down()
{
   set_state(STATE_WALKING_DOWN);
}



void KnightEntity::walk_left()
{
   set_state(STATE_WALKING_UP);
}



void KnightEntity::walk_right()
{
   set_state(STATE_WALKING_RIGHT);
}



void KnightEntity::take_hit()
{
   set_state(STATE_TAKING_HIT);
}



bool KnightEntity::is_busy()
{
   return state_counter > 0.0;
}



void KnightEntity::set_state(state_t new_state)
{
   state = new_state;

   switch (state)
   {
   case STATE_DYING:
      UserEventEmitter::emit_event(PLAY_SOUND_EFFECT, 0, (intptr_t)(new std::string(DYING_ENEMY_SOUND_EFFECT)));
      flag_for_deletion();
      break;
   case STATE_TAKING_HIT:
      health -= 1;
      if (health <= 0)
      {
         set_state(STATE_DYING);
      }
      else
      {
         velocity.position = vec2d(0.0, 0.0);
         UserEventEmitter::emit_event(PLAY_SOUND_EFFECT, 0, (intptr_t)(new std::string(METAL_KLANK_SOUND_EFFECT)));
         UserEventEmitter::emit_event(SPAWN_MOTION_FX, (intptr_t)(new std::string(MOTION_FX_DAMAGE_HIT)), place.position.x, place.position.y, (intptr_t)(new std::string("HIT!")));
         reveal_behavior();
      }
      break;
   case STATE_ATTACKING:
      EntityFactory::create_enemy_attack_damage_zone(get_parent(), place.position.x-150, place.position.y, 150, 50);
      bitmap.bitmap(sprite_sheet->get_sprite(35));
      state_counter = 0.3;
      break;
   case STATE_STANDING_STILL:
      velocity.position = vec2d(0.0, 0.0);
      break;
   case STATE_WALKING_UP:
      velocity.position = vec2d(0.0, -walk_speed/2);
      break;
   case STATE_WALKING_DOWN:
      velocity.position = vec2d(0.0, walk_speed/2);
      break;
   case STATE_WALKING_LEFT:
      velocity.position = vec2d(-walk_speed, 0.0);
      break;
   case STATE_WALKING_RIGHT:
      velocity.position = vec2d(walk_speed, 0.0);
      break;
   }
}



ALLEGRO_COLOR KnightEntity::get_identity_color()
{
   ALLEGRO_COLOR identity_color;

   switch(behavior)
   {
   case BEHAVIOR_NORMAL:
      identity_color = color::firebrick;
      break;
   }

   return identity_color;
}



float KnightEntity::get_identity_tint_intensity()
{
   float strobe_speed = 3.0;
   float identiy_reveal_duration = 4.0;

   switch (behavior)
   {
   case BEHAVIOR_NORMAL:
      strobe_speed = 3.0;
      break;
   }

   float normalized_oscilation = sin(al_get_time() * strobe_speed*4) * 0.5 + 0.5;
   float tint_intensity = 1.0 - std::min(identity_reveal_counter*(1.0/identiy_reveal_duration), 1.0);

   return normalized_oscilation * interpolator::fast_in(tint_intensity);
}



std::string KnightEntity::get_name()
{
   return name;
}



