#pragma once



#include <models/entities/entity_base.hpp>
#include <models/sprite_sheet.hpp>



class KrampusEntity : public EntityBase
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
   BitmapObject club_bitmap;
   BitmapObject shield_bitmap;
   SpriteSheet *sprite_sheet;

   bool set_state(state_t new_state, bool override_if_busy=false);

public:
   KrampusEntity(ElementID *parent, SpriteSheet *sprite_sheet, float x, float y);
   virtual ~KrampusEntity();

   void update() override;
   void draw() override;

   void attack();
   void take_hit();
   void block();
   void stand_still();
   void celebrate();
   void walk_up();
   void walk_down();
   void walk_left();
   void walk_right();
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



