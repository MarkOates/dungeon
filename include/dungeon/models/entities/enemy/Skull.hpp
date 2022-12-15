#pragma once


#include <dungeon/models/entities/enemy/base.hpp>


class SpriteSheet;


namespace Enemy
{
   class Skull : public Base
   {
   public:
      enum state_t
      {
         STATE_NONE,
         STATE_MOVING,
         STATE_TAKE_DAMAGE,
         STATE_DYING,
         STATE_DEAD,
      };

   private:
      AllegroFlare::EventEmitter *event_emitter;
      float state_counter;
      float min_y, max_y;
      SpriteSheet *sprite_sheet;
      state_t state;
      int health;

   public:
      Skull(AllegroFlare::ElementID *parent, AllegroFlare::EventEmitter *event_emitter, SpriteSheet *sprite_sheet, float x, float y, float min_y, float max_y);
      ~Skull();

      void set_state(state_t state);

      void update() override;
      void draw() override;
      void take_hit() override;
   };
}


