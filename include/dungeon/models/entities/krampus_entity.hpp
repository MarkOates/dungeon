#pragma once


#include <dungeon/models/entities/base.hpp>
#include <dungeon/models/sprite_sheet.hpp>

#include <DungeonPlus/AnimationBook.hpp> // for FULL_ROTATION


class KrampusEntity : public Entity::Base
{
public:
   enum state_t
   {
      WALKING_UP,
      WALKING_DOWN,
      WALKING_RIGHT,
      WALKING_LEFT,
      BLOCKING,
      STANDING,
      CELEBRATING,
      ATTACKING,
      TAKING_HIT,
      USING_MAGIC,
      DEAD
   };
   int state;
   int health;
   float state_counter;
   bool state_is_busy;
   int walking_speed;
   bool facing_right;
   bool _has_weapon;
   bool _has_shield;
   bool _has_stone_of_defiance;

   bool stunned_from_hit;
   float stunned_from_hit_counter;
   float stunned_from_hit_duration;

   BitmapObject club_bitmap;
   BitmapObject shield_bitmap;
   SpriteSheet *sprite_sheet;
   DungeonPlus::AnimationBook *animation_book;
   AllegroFlare::EventEmitter *event_emitter;
   AllegroFlare::Shader *flat_color_shader;

   bool set_state(state_t new_state, bool override_if_busy=false);

public:
   KrampusEntity(
         AllegroFlare::ElementID *parent,
         AllegroFlare::EventEmitter *event_emitter,
         AllegroFlare::Shader *flat_color_shader,
         SpriteSheet *sprite_sheet,
         DungeonPlus::AnimationBook *animation_book,
         float x,
         float y
      );
   virtual ~KrampusEntity();

   void update() override;
   void draw() override;

   ALLEGRO_COLOR get_hurt_color();
   float get_hurt_tint_intensity();

   void attack();
   void take_hit();
   void block();
   void stand_still();
   void celebrate();
   void walk_up();
   void walk_down();
   void walk_left();
   void walk_right();
   void stand_still_if_no_velocity();
   void face_left();
   void face_right();
   void use_stone_of_defiance();

   void get_weapon();
   void get_shield();
   void get_stone_of_defiance();

   bool is_idle();
   bool has_weapon();
   bool has_shield();
};


