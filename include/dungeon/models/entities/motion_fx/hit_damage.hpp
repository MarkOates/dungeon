#pragma once


#include <dungeon/models/entities/motion_fx/base.hpp>
#include <framework/objects/text_object.hpp>
#include <allegro5/allegro_font.h>


namespace MotionFX
{
   class HitDamage : public Base
   {
   private:
      ALLEGRO_FONT *font;
      TextObject text_object;

   public:
      HitDamage(ElementID *parent, float x, float y, std::string damage_string);
      ~HitDamage();

      void update() override;
      void draw() override;
   };
}


