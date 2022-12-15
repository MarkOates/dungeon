

#include <dungeon/models/entities/enemy/Skull.hpp>

#include <dungeon/emitters/user_event_emitter.hpp>
#include <dungeon/factories/entity_factory.hpp>
#include <dungeon/models/sprite_sheet.hpp>
#include <dungeon/motion_fx_type_names.hpp>
#include <dungeon/music_track_nums.hpp>
#include <dungeon/user_events.hpp>
#include <allegro5/allegro_primitives.h>
#include <AllegroFlare/Color.hpp>
#include <cmath>


namespace Enemy
{


Skull::Skull(AllegroFlare::ElementID *parent, AllegroFlare::EventEmitter *event_emitter, SpriteSheet *sprite_sheet, float x, float y, float min_y, float max_y)
   : Enemy::Base(parent, "skull", x, y, 3)
   , state_counter(0.0)
   , min_y(min_y)
   , max_y(max_y)
   , event_emitter(event_emitter)
   , sprite_sheet(sprite_sheet)
   , state(STATE_NONE)
   , health(3)
{
   if (!event_emitter) throw std::runtime_error("Skull:: no event emitter");

   place.size = { 100, 40 };
   velocity.position = { -3, 2 };
   bitmap.position(place.size.x/2, place.size.y);
   bitmap.scale(2, 2);
   bitmap.align(0.5, 1.0);

   set_state(STATE_MOVING);
}


Skull::~Skull()
{
}


void Skull::set_state(state_t new_state)
{
   state = new_state;

   switch(state)
   {
   case STATE_MOVING:
      bitmap.bitmap(sprite_sheet->get_sprite(36));
      break;
   case STATE_TAKE_DAMAGE:
      state_counter = 0.4;
      health -= 1;
      bitmap.bitmap(sprite_sheet->get_sprite(38));
      if (health <= 0) set_state(STATE_DYING);
      break;
   case STATE_DYING:
      bitmap.bitmap(sprite_sheet->get_sprite(38));
      state_counter = 1.0;
      break;
   case STATE_DEAD:
      event_emitter->emit_event(PLAY_SOUND_EFFECT, 0, (intptr_t)(new std::string(DYING_ENEMY_SOUND_EFFECT)));
      event_emitter->emit_event(SPAWN_MOTION_FX, (intptr_t)(new std::string(MOTION_FX_SLASH_POOF)), place.position.x, place.position.y);
      flag_for_deletion();
      break;
   default:
      break;
   }
}


void Skull::update()
{
   switch (state)
   {
   case STATE_MOVING:
      if (place.position.y <= min_y) velocity.position.y = 2;
      if (place.position.y >= max_y) velocity.position.y = -2;
      place += velocity;
      if (((int)(al_get_time() * 4.0) % 2) < 1.0) bitmap.bitmap(sprite_sheet->get_sprite(36));
      else bitmap.bitmap(sprite_sheet->get_sprite(37));
      if (place.x <= 0) set_state(STATE_DYING);
      EntityFactory::create_enemy_attack_damage_zone(get_parent(), place.position.x, place.position.y, place.size.x, place.size.y);
      break;
   case STATE_TAKE_DAMAGE:
      state_counter -= 1.0/60.0;
      if (state_counter <= 0)
      {
         set_state(STATE_MOVING);
         state_counter = 0.0;
      }
      break;
   case STATE_DYING:
      state_counter -= 1.0/60.0;
      if (state_counter <= 0)
      {
         set_state(STATE_DEAD);
         state_counter = 0.0;
      }
      break;
   case STATE_DEAD:
      break;
   default:
      break;
   }
}


void Skull::draw()
{
   place.start_transform();
   bitmap.draw();
   al_draw_filled_rectangle(0, 0, place.w, place.h, AllegroFlare::color::yellow);
   place.restore_transform();
}


void Skull::take_hit()
{
   if (!STATE_MOVING) return;
   set_state(STATE_TAKE_DAMAGE);
}


} // namespace Enemy


