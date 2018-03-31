#pragma once



#include <models/entities/enemies/enemy_base.hpp>

#include <framework/shader.hpp>
#include <models/sprite_sheet.hpp>



enum knight_behavior_t
{
   BEHAVIOR_NORMAL
};



class KnightEntity : public EnemyBase
{
private:
   enum state_t
   {
      STATE_ATTACKING,
      STATE_STANDING_STILL,
      STATE_TAKING_HIT,
      STATE_WALKING_UP,
      STATE_WALKING_DOWN,
      STATE_WALKING_LEFT,
      STATE_WALKING_RIGHT,
      STATE_DYING,
   };

   SpriteSheet *sprite_sheet;
   knight_behavior_t behavior;
   std::string name;
   float state_counter;
   float walk_speed;
   state_t state;
   Shader *flat_color_shader;
   float identity_reveal_counter;
   ALLEGRO_BITMAP *knight_bitmap, *identity_bitmap;
   ALLEGRO_COLOR get_identity_color();
   float get_identity_tint_intensity();
   int health;

   void set_state(state_t);

   friend class AIKnightController;

public:
   KnightEntity(ElementID *parent, SpriteSheet *sprite_sheet, Shader *flat_color_shader, float x, float y, std::string name, knight_behavior_t behavior, int sprite_index, int identity_sprite_index);
   virtual ~KnightEntity();

   void update() override;
   void draw() override;

   void attack();
   void stand_still();
   void walk_up();
   void walk_down();
   void walk_left();
   void walk_right();
   void take_hit() override;

   bool is_busy();

   void reveal_behavior();
   std::string get_name();
};



