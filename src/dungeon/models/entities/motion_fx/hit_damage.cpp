


#include <dungeon/models/entities/motion_fx/hit_damage.hpp>
#include <dungeon/entity_attribute_names.hpp>
//#include <framework/framework.hpp>
#include <AllegroFlare/Interpolators.hpp>



namespace MotionFX
{



HitDamage::HitDamage(ElementID *parent, ALLEGRO_FONT *font, float x, float y, std::string damage_string)
   : Base(parent, "hit_damage", x, y, 1.5)
   , font(font)
   , text_object(damage_string)
{
   if (!font) throw std::runtime_error("HitDamage:: missing font");

   text_object.position(0, 0)
      .font(font)
      .align(0.5, 1.0)
      //.color(color::white) // NOTE THIS change
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
   text_object.anchor(0.0, -AllegroFlare::interpolator::bounce_in(normalized_bounce_value)*100);
}



void HitDamage::draw()
{
   place.start_transform();
   text_object.draw();
   place.restore_transform();
}



}



