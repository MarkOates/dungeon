#pragma once



#include <models/entities/motion_fx/motion_fx_base.hpp>
#include <allegro5/allegro_font.h>
#include <framework/objects/text_object.hpp>



class MotionFXHitDamage : public MotionFXBase
{
private:
   ALLEGRO_FONT *font;
   TextObject text_object;

public:
   MotionFXHitDamage(ElementID *parent, float x, float y, std::string damage_string);
   ~MotionFXHitDamage();

   void update() override;
   void draw() override;
};



