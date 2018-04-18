


#include <dungeon/models/entities/motion_fx/hit_damage.hpp>
#include <dungeon/entity_attribute_names.hpp>
#include <framework/framework.hpp>



namespace MotionFX
{



HitDamage::HitDamage(ElementID *parent, float x, float y, std::string damage_string)
   : Base(parent, "hit_damage", x, y, 1.5)
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



HitDamage::~HitDamage()
{
}



void HitDamage::update()
{
   Base::update();

   float normalized_bounce_value = std::max(0.0, (counter*0.1) / (duration*0.1));
   text_object.anchor(0.0, -interpolator::bounce_in(normalized_bounce_value)*100);
}



void HitDamage::draw()
{
   place.start_transform();
   text_object.draw();
   place.restore_transform();
}



}



