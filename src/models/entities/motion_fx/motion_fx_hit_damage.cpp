


#include <models/entities/motion_fx/motion_fx_hit_damage.hpp>
#include <framework/framework.hpp>
#include <entity_attribute_names.hpp>



MotionFXHitDamage::MotionFXHitDamage(ElementID *parent, float x, float y, std::string damage_string)
   : MotionFXBase(parent, "hit_damage", x, y, 1.5)
   , font(Framework::font("ChronoTrigger.ttf 20"))
   , text_object(damage_string)
{
   text_object.position(0, 0)
      .font(font)
      .align(0.5, 1.0)
      .color(color::white)
      .scale(3);

   set(ALWAYS_ON_TOP);
}



MotionFXHitDamage::~MotionFXHitDamage()
{
}



void MotionFXHitDamage::update()
{
   MotionFXBase::update();

   float normalized_bounce_value = std::max(0.0, (counter*0.1) / (duration*0.1));
   text_object.anchor(0.0, -interpolator::bounce_in(normalized_bounce_value)*100);
}



void MotionFXHitDamage::draw()
{
   place.start_transform();
   text_object.draw();
   place.restore_transform();
}



