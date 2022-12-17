#pragma once


#include <AllegroFlare/ElementID.hpp>
#include <AllegroFlare/EventEmitter.hpp>
#include <AllegroFlare/Placement2D.hpp>
#include <AllegroFlare/Shader.hpp>
#include <DungeonPlus/Animation.hpp>
#include <DungeonPlus/AnimationBook.hpp>
#include <allegro5/allegro.h>
#include <dungeon/models/bitmap_object.hpp>
#include <string>


namespace DungeonPlus
{
   class Sprite : public AllegroFlare::ElementID
   {
   public:
      static constexpr bool STUNNED_FROM_HIT_DURATION = false;

   private:
      DungeonPlus::AnimationBook* animation_book;
      AllegroFlare::EventEmitter* event_emitter;
      AllegroFlare::Shader* flat_color_shader;
      AllegroFlare::Placement2D place;
      AllegroFlare::Placement2D velocity;
      BitmapObject bitmap_object;
      DungeonPlus::Animation animation;
      int health;
      bool stunned_from_hit;
      float stunned_from_hit_counter;
      bool initialized;

   protected:


   public:
      Sprite(DungeonPlus::AnimationBook* animation_book=nullptr, AllegroFlare::EventEmitter* event_emitter=nullptr, AllegroFlare::Shader* flat_color_shader=nullptr);
      ~Sprite();

      void initialize();
      void set_animation(std::string name="[unset-name]");
      void update();
      void draw();
      ALLEGRO_COLOR get_hurt_color();
      float get_hurt_tint_intensity();
   };
}



