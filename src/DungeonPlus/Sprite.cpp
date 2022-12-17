

#include <DungeonPlus/Sprite.hpp>

#include <AllegroFlare/Color.hpp>
#include <AllegroFlare/Interpolators.hpp>
#include <cmath>
#include <iostream>
#include <sstream>
#include <stdexcept>


namespace DungeonPlus
{


Sprite::Sprite(DungeonPlus::AnimationBook* animation_book, AllegroFlare::EventEmitter* event_emitter, AllegroFlare::Shader* flat_color_shader)
   : AllegroFlare::ElementID()
   , animation_book(animation_book)
   , event_emitter(event_emitter)
   , flat_color_shader(flat_color_shader)
   , place({})
   , velocity({})
   , bitmap_object({})
   , animation({})
   , health(1)
   , stunned_from_hit(false)
   , stunned_from_hit_counter(0.0f)
   , initialized(false)
{
}


Sprite::~Sprite()
{
}


void Sprite::initialize()
{
   if (!((!initialized)))
   {
      std::stringstream error_message;
      error_message << "[Sprite::initialize]: error: guard \"(!initialized)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("Sprite::initialize: error: guard \"(!initialized)\" not met");
   }
   if (!(animation_book))
   {
      std::stringstream error_message;
      error_message << "[Sprite::initialize]: error: guard \"animation_book\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("Sprite::initialize: error: guard \"animation_book\" not met");
   }
   if (!(event_emitter))
   {
      std::stringstream error_message;
      error_message << "[Sprite::initialize]: error: guard \"event_emitter\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("Sprite::initialize: error: guard \"event_emitter\" not met");
   }
   if (!(flat_color_shader))
   {
      std::stringstream error_message;
      error_message << "[Sprite::initialize]: error: guard \"flat_color_shader\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("Sprite::initialize: error: guard \"flat_color_shader\" not met");
   }
   //set("type", type); // doesn't seem necessary at the moment
   velocity.scale = { 0, 0 };
   velocity.align = { 0, 0 };

   set("bound_in_world");

   set_animation("blob"); // to start

   initialized = true;
   return;
}

void Sprite::set_animation(std::string name)
{
   animation = animation_book->get_animation_by_name(name);
   animation.initialize();
   animation.start();
   return;
}

void Sprite::update()
{
   // update the hit counter
   if (stunned_from_hit)
   {
      stunned_from_hit_counter -= 1.0 / 60.0f;
      if (stunned_from_hit_counter < 0.0f)
      {
         stunned_from_hit = false;
         stunned_from_hit_counter = 0.0f;
      }
   }

   // update the position
   place += velocity;

   // update the animation
   animation.update();

   return;
}

void Sprite::draw()
{
   bitmap_object.bitmap(animation.get_frame_now());

   flat_color_shader->activate();

   ALLEGRO_COLOR hurt_color = get_hurt_color();
   float tint_intensity = stunned_from_hit ? get_hurt_tint_intensity() : 0.0f;

   flat_color_shader->activate();
   flat_color_shader->set_vec3("tint", hurt_color.r, hurt_color.g, hurt_color.b);
   flat_color_shader->set_float("tint_intensity", tint_intensity);

   place.start_transform();
      bitmap_object.start_transform();
      bitmap_object.draw_raw();
      //if (has_weapon()) club_bitmap.draw();
      //if (has_shield()) shield_bitmap.draw();
      bitmap_object.restore_transform();
   place.restore_transform();

   flat_color_shader->set_float("tint_intensity", 0.0f);
   flat_color_shader->deactivate();
   return;
}

ALLEGRO_COLOR Sprite::get_hurt_color()
{
   ALLEGRO_COLOR hurt_color;
   hurt_color = AllegroFlare::color::firebrick;
   return hurt_color;
}

float Sprite::get_hurt_tint_intensity()
{
   float strobe_speed = 3.0;
   float identiy_reveal_duration = 4.0;

   float normalized_oscilation = sin(al_get_time() * strobe_speed*4) * 0.5 + 0.5;
   float tint_intensity = std::min(stunned_from_hit_counter*(1.0/STUNNED_FROM_HIT_DURATION), 1.0);

   return normalized_oscilation * AllegroFlare::interpolator::fast_in(tint_intensity);
}


} // namespace DungeonPlus


