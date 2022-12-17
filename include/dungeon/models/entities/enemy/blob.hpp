#pragma once


#include <dungeon/models/entities/enemy/base.hpp>

//#include <framework/shader.hpp>
#include <dungeon/models/sprite_sheet.hpp>
#include <AllegroFlare/Shader.hpp>
#include <AllegroFlare/Random.hpp>
#include <DungeonPlus/Animation.hpp>
#include <DungeonPlus/AnimationBook.hpp>


class Blob : public Enemy::Base
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
   std::string name;
   float walk_speed;
   state_t state;
   AllegroFlare::Shader *flat_color_shader;
   SpriteSheet *sprite_sheet;
   DungeonPlus::AnimationBook *animation_book;
   DungeonPlus::Animation animation;

   // health
   float hurt_reveal_counter;
   ALLEGRO_COLOR get_hurt_color();
   float get_hurt_tint_intensity();
   int health;

   void set_animation(std::string name);
   void set_state(state_t);

   friend class AIKidController;

public:

   Blob(
      ElementID *parent,
      AllegroFlare::EventEmitter *event_emitter,
      SpriteSheet *sprite_sheet,
      AllegroFlare::Shader *flat_color_shader,
      DungeonPlus::AnimationBook *animation_book,
      float x,
      float y,
      std::string name
   );
   virtual ~Blob();

   void update() override;
   void draw() override;

   void stand_still();
   void walk_up();
   void walk_down();
   void walk_left();
   void walk_right();
   void take_hit() override;

   void reveal_hurt();
   std::string get_name();
};


