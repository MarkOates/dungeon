


#include <dungeon/models/entities/krampus_entity.hpp>

#include <dungeon/emitters/user_event_emitter.hpp>
#include <dungeon/factories/entity_factory.hpp>
#include <dungeon/music_track_nums.hpp>
#include <dungeon/user_events.hpp>
#include <cmath>


#include <AllegroFlare/Useful.hpp> // for FULL_ROTATION
using AllegroFlare::FULL_ROTATION;


KrampusEntity::KrampusEntity(
      AllegroFlare::ElementID *parent,
      AllegroFlare::EventEmitter *event_emitter,
      AllegroFlare::Shader *flat_color_shader,
      SpriteSheet *sprite_sheet,
      DungeonPlus::AnimationBook *animation_book,
      float x,
      float y
    )
   : Entity::Base(parent, "krampus", x, y)
   , animation_book(animation_book)
   , event_emitter(event_emitter)
   , flat_color_shader(flat_color_shader)
   , state_is_busy(false)
   , health(3)
   , walking_speed(8.0)
   , facing_right(true)
   , _has_weapon(false)
   , _has_stone_of_defiance(false)
   , stunned_from_hit(false)
   , stunned_from_hit_counter(0.0f)
   , stunned_from_hit_duration(2.0f)
   , club_bitmap(nullptr)
   , shield_bitmap(nullptr)
   , state(STANDING)
   , sprite_sheet(sprite_sheet)
{
   if (!event_emitter) throw std::runtime_error("KrampusEntity:: no event_emitter");
   if (!flat_color_shader) throw std::runtime_error("KrampusEntity:: no flat_color_shader");
   if (!animation_book) throw std::runtime_error("KrampusEntity:: no animation_book");

   place.size = { 120, 30 };
   //bitmap.bitmap(sprite_sheet->get_sprite(18));
   bitmap.bitmap(sprite_sheet->get_sprite(26)); //sprite_sheet->get_sprite(18));
   bitmap.align(0.5, 1.0);
   bitmap.scale(2.0, 2.0);
   bitmap.position(place.size.x/2, place.size.y/2);

   //club_bitmap.bitmap(sprite_sheet->get_sprite(23));
   club_bitmap.bitmap(sprite_sheet->get_sprite(23));
   club_bitmap.align(0.5, 0.95);

   //shield_bitmap.bitmap(sprite_sheet->get_sprite(28));
   shield_bitmap.bitmap(sprite_sheet->get_sprite(37));
   shield_bitmap.align(0.5, 0.5);
   shield_bitmap.flags(ALLEGRO_FLIP_HORIZONTAL);

   set("bound_in_world");

   set_state(STANDING, true);
   get_shield();
}



KrampusEntity::~KrampusEntity()
{
}



void KrampusEntity::update()
{
   if (stunned_from_hit)
   {
      stunned_from_hit_counter -= 1.0 / 60.0f;
      if (stunned_from_hit_counter < 0.0f)
      {
         stunned_from_hit = false;
         stunned_from_hit_counter = 0.0f;
      }
   }

   float previous_state_counter = state_counter;
   state_counter += 1.0 / 60.0;
   place += velocity;

   switch(state)
   {
   case WALKING_UP:
   case WALKING_DOWN:
   case WALKING_LEFT:
   case WALKING_RIGHT:
      {
         float bounce_counter = sin(al_get_time()*36)*0.5 + 0.5;
         bitmap.anchor(0, bounce_counter * -12);
      }
      break;
   case STANDING:
      break;
   case BLOCKING:
      break;
   case ATTACKING:
      {
         float scale = 2.0;
         if (state_counter*scale >= 0.4 && previous_state_counter*scale < 0.4)
         {
            //bitmap.bitmap(sprite_sheet->get_sprite(20));
            club_bitmap.position(bitmap.w()/2+30, 25);
            club_bitmap.rotation(FULL_ROTATION * 0.05);
         }
         if (state_counter*scale >= 0.5 && previous_state_counter*scale < 0.5)
         {
            //bitmap.bitmap(sprite_sheet->get_sprite(21));
            club_bitmap.position(bitmap.w()/2 + 36, bitmap.h()-20);
            club_bitmap.rotation(FULL_ROTATION * 0.25 + 0.1);

            float dh = place.size.y;
            float dy = place.position.y;
            float dw = 80;
            float dx = facing_right ? place.position.x + place.size.x : place.position.x - place.size.x;
            if (has_weapon())
            {
               event_emitter->emit_event(PLAY_SOUND_EFFECT, STRONG_PUNCH_SOUND_EFFECT);
               //UserEventEmitter::emit_event(PLAY_SOUND_EFFECT, STRONG_PUNCH_SOUND_EFFECT);
               EntityFactory::create_krampus_attack_damage_zone_with_club(get_parent(), dx, dy, dw*2, dh);
            }
            else EntityFactory::create_krampus_attack_damage_zone(get_parent(), dx, dy, dw, dh);
         }
         if (state_counter*scale >= 0.7 && previous_state_counter*scale < 0.7)
         {
            //bitmap.bitmap(sprite_sheet->get_sprite(22));
            club_bitmap.position(bitmap.w()/2 + 36, bitmap.h()-20);
            club_bitmap.rotation(FULL_ROTATION * 0.25 - 0.2);
         }
         if (state_counter*scale >= 1.0 && previous_state_counter*scale < 1.0)
         {
            set_state(STANDING, true);
         }
         break;
      }
   case CELEBRATING:
      {
         float previous_state_counter_modded = std::fmod(previous_state_counter, 0.4);
         float state_counter_modded = std::fmod(state_counter, 0.4);
         float scale = 1.0;
         //if (state_counter_modded*scale >= 0.1 && previous_state_counter_modded*scale < 0.1) bitmap.bitmap(sprite_sheet->get_sprite(19));
         //if (state_counter_modded*scale >= 0.3 && previous_state_counter_modded*scale < 0.3) bitmap.bitmap(sprite_sheet->get_sprite(18));
      }
      break;
   case USING_MAGIC:
      if (state_counter >= 1.6 && previous_state_counter < 1.6) set_state(STANDING, true);
      break;
   default:
      break;
   }
}



ALLEGRO_COLOR KrampusEntity::get_hurt_color()
{
   ALLEGRO_COLOR hurt_color;
   hurt_color = AllegroFlare::color::firebrick;
   return hurt_color;
}



float KrampusEntity::get_hurt_tint_intensity()
{
   float strobe_speed = 4.0;
   //float stunned_from_hit_duration = 4.0;

   float normalized_oscilation = sin(al_get_time() * strobe_speed*4) * 0.5 + 0.5;
   float tint_intensity =
      std::min(stunned_from_hit_counter*(1.0/stunned_from_hit_duration), 1.0);

   return normalized_oscilation;// * AllegroFlare::interpolator::fast_in(tint_intensity);
}





void KrampusEntity::draw()
{
   flat_color_shader->activate();

   ALLEGRO_COLOR hurt_color = get_hurt_color();
   float tint_intensity = stunned_from_hit ? get_hurt_tint_intensity() : 0.0f;

   flat_color_shader->activate();
   flat_color_shader->set_vec3("tint", hurt_color.r, hurt_color.g, hurt_color.b);
   flat_color_shader->set_float("tint_intensity", tint_intensity);

   place.start_transform();
   bitmap.start_transform();
   bitmap.draw_raw();
   if (has_weapon()) club_bitmap.draw();
   if (has_shield()) shield_bitmap.draw();
   bitmap.restore_transform();
   place.restore_transform();

   flat_color_shader->set_float("tint_intensity", 0.0f);
   flat_color_shader->deactivate();
}



void KrampusEntity::attack()
{
   set_state(ATTACKING);
}



void KrampusEntity::take_hit()
{
   if (stunned_from_hit) return;
   set_state(TAKING_HIT);
}



void KrampusEntity::block()
{
   set_state(BLOCKING);
}



void KrampusEntity::stand_still()
{
   set_state(STANDING);
}



void KrampusEntity::walk_up()
{
   set_state(WALKING_UP);
}



void KrampusEntity::walk_down()
{
   set_state(WALKING_DOWN);
}



void KrampusEntity::walk_left()
{
   set_state(WALKING_LEFT);
}



void KrampusEntity::walk_right()
{
   set_state(WALKING_RIGHT);
}



void KrampusEntity::stand_still_if_no_velocity()
{
   //if (abs(velocity.position.x) < 0.001) && abs(velocity.position.y)
   if (state == STANDING) return;
   if (velocity.position.get_magnitude_squared() < 0.001)
   {
      set_state(STANDING);
   }
}



void KrampusEntity::face_left()
{
   facing_right = false;
   bitmap.flip(true, false);
}



void KrampusEntity::face_right()
{
   facing_right = true;
   bitmap.flip(false, false);
}



void KrampusEntity::celebrate()
{
   set_state(CELEBRATING);
}



void KrampusEntity::use_stone_of_defiance()
{
   if (_has_stone_of_defiance) set_state(USING_MAGIC);
}



bool KrampusEntity::set_state(state_t new_state, bool override_if_busy)
{
   if (override_if_busy) state_is_busy = false;

   if (state_is_busy) return false;

   state_counter = 0.0;
   state = new_state;

   switch(new_state)
   {
   case WALKING_UP:
      //bitmap.bitmap(sprite_sheet->get_sprite(18));
      //velocity.position = { 0.0, -walking_speed/2.0f };
      velocity.position.y = -walking_speed/2.0f;
      shield_bitmap.flip(true, false);
      break;
   case WALKING_DOWN:
      //bitmap.bitmap(sprite_sheet->get_sprite(18));
      //velocity.position = { 0.0, walking_speed/2.0f };
      velocity.position.y = walking_speed/2.0f;
      shield_bitmap.flip(true, false);
      break;
   case WALKING_LEFT:
      //bitmap.bitmap(sprite_sheet->get_sprite(18));
      face_left();
      //velocity.position = { (float)-walking_speed, 0.0 };
      velocity.position.x = -walking_speed;
      shield_bitmap.flip(true, false);
      break;
   case WALKING_RIGHT:
      //bitmap.bitmap(sprite_sheet->get_sprite(18));
      face_right();
      //velocity.position = { (float)walking_speed, 0.0 };
      velocity.position.x = walking_speed;
      shield_bitmap.flip(true, false);
      break;
   case TAKING_HIT:
      health--;
      if (health <= 0)
      {
         // this hit killed player
         event_emitter->emit_event(PLAYER_DIED_EVENT);
         velocity.position = { 0.0, 0.0 };
         event_emitter->emit_event(PLAY_SOUND_EFFECT, 0, (intptr_t)(new std::string(KRAMPUS_HIT_SOUND_EFFECT)));
      }
      else
      {
         // took hit, now stunned
         stunned_from_hit = true;
         stunned_from_hit_counter = stunned_from_hit_duration;
         velocity.position = { 0.0, 0.0 };
         event_emitter->emit_event(PLAY_SOUND_EFFECT, 0, (intptr_t)(new std::string(KRAMPUS_HIT_SOUND_EFFECT)));
      }
      break;
   case BLOCKING:
      bitmap.anchor(0, 0);
      //bitmap.bitmap(sprite_sheet->get_sprite(23));
      velocity.position = { 0.0, 0.0 };
      shield_bitmap.position(bitmap.w() * 0.7, bitmap.h() * 0.72);
      shield_bitmap.rotation(-0.07);
      shield_bitmap.flip(false, false);
      break;
   case STANDING:
      bitmap.anchor(0, 0);
      //bitmap.bitmap(sprite_sheet->get_sprite(18));
      velocity.position = { 0.0, 0.0 };
      club_bitmap.position(bitmap.w()/2 + 36, bitmap.h()-20);
      club_bitmap.rotation(FULL_ROTATION * 0.25 - 0.2);
      shield_bitmap.position(bitmap.w() * 0.3, bitmap.h() * 0.78);
      shield_bitmap.rotation(0.07);
      shield_bitmap.flip(true, false);
      break;
   case ATTACKING:
      bitmap.anchor(0, 0);
      state_is_busy = true;
      //bitmap.bitmap(sprite_sheet->get_sprite(19));
      velocity.position = { 0.0, 0.0 };
      club_bitmap.position(bitmap.w()/2, 10);
      club_bitmap.rotation(FULL_ROTATION * -0.2);
      shield_bitmap.position(bitmap.w() * 0.3, bitmap.h() * 0.78);
      shield_bitmap.flip(true, false);
      break;
   case CELEBRATING:
      bitmap.anchor(0, 0);
      //bitmap.bitmap(sprite_sheet->get_sprite(19));
      velocity.position = { 0.0, 0.0 };
      shield_bitmap.flip(true, false);
      break;
   case USING_MAGIC:
      bitmap.anchor(0, 0);
      state_is_busy = true;
      //bitmap.bitmap(sprite_sheet->get_sprite(19));
      velocity.position = { 0.0, 0.0 };
      //UserEventEmitter::emit_event(USE_STONE_OF_DEFIANCE_EVENT);
      event_emitter->emit_event(USE_STONE_OF_DEFIANCE_EVENT);
      shield_bitmap.flip(true, false);
      break;
   default:
      return false;
      break;
   }

   return true;
}



void KrampusEntity::get_weapon()
{
   _has_weapon = true;
}



void KrampusEntity::get_shield()
{
   _has_shield = true;
}



void KrampusEntity::get_stone_of_defiance()
{
   _has_stone_of_defiance = true;
}



bool KrampusEntity::is_idle()
{
   return state == STANDING;
}



bool KrampusEntity::has_weapon()
{
   return _has_weapon;
}



bool KrampusEntity::has_shield()
{
   return _has_shield;
}



