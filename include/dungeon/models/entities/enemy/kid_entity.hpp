#pragma once


#include <dungeon/models/entities/enemy/base.hpp>

//#include <framework/shader.hpp>
#include <dungeon/models/sprite_sheet.hpp>
#include <AllegroFlare/Shader.hpp>
#include <AllegroFlare/Random.hpp>


enum behavior_t
{
   BEHAVIOR_ADULT,
   BEHAVIOR_NAUGHTY,
   BEHAVIOR_NICE
};


class KidEntity : public Enemy::Base
{
private:
   enum state_t
   {
      STATE_STANDING_STILL,
      STATE_TAKING_HIT,
      STATE_WALKING_UP,
      STATE_WALKING_DOWN,
      STATE_WALKING_LEFT,
      STATE_WALKING_RIGHT
   };

   AllegroFlare::Random random;
   AllegroFlare::EventEmitter *event_emitter;
   behavior_t behavior;
   std::string name;
   float walk_speed;
   state_t state;
   AllegroFlare::Shader *flat_color_shader;
   float identity_reveal_counter;
   ALLEGRO_BITMAP *kid_bitmap, *identity_bitmap;
   ALLEGRO_COLOR get_identity_color();
   float get_identity_tint_intensity();
   int health;

   void set_state(state_t);

   friend class AIKidController;

public:
   KidEntity(ElementID *parent, AllegroFlare::EventEmitter *event_emitter, SpriteSheet *sprite_sheet, AllegroFlare::Shader *flat_color_shader, float x, float y, std::string name, behavior_t behavior, int sprite_index, int identity_sprite_index);
   virtual ~KidEntity();

   void update() override;
   void draw() override;

   void stand_still();
   void walk_up();
   void walk_down();
   void walk_left();
   void walk_right();
   void take_hit() override;

   void reveal_behavior();
   std::string get_name();
};


