

#include <DungeonPlus/Gameplay.hpp>

#include <iostream>
#include <sstream>
#include <stdexcept>


namespace DungeonPlus
{


Gameplay::Gameplay(DungeonPlus::AnimationBook* animation_book, AllegroFlare::EventEmitter* event_emitter, AllegroFlare::Shader* flat_color_shader)
   : AllegroFlare::Screens::Base(DungeonPlus::Gameplay::TYPE)
   , animation_book(animation_book)
   , event_emitter(event_emitter)
   , flat_color_shader(flat_color_shader)
   , scene_factory({})
   , scene(nullptr)
   , initialized(false)
{
}


Gameplay::~Gameplay()
{
}


void Gameplay::set_animation_book(DungeonPlus::AnimationBook* animation_book)
{
   if (!((!initialized)))
   {
      std::stringstream error_message;
      error_message << "[Gameplay::set_animation_book]: error: guard \"(!initialized)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("Gameplay::set_animation_book: error: guard \"(!initialized)\" not met");
   }
   this->animation_book = animation_book;
   return;
}

void Gameplay::set_event_emitter(AllegroFlare::EventEmitter* event_emitter)
{
   if (!((!initialized)))
   {
      std::stringstream error_message;
      error_message << "[Gameplay::set_event_emitter]: error: guard \"(!initialized)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("Gameplay::set_event_emitter: error: guard \"(!initialized)\" not met");
   }
   this->event_emitter = event_emitter;
   return;
}

void Gameplay::set_flat_color_shader(AllegroFlare::Shader* flat_color_shader)
{
   if (!((!initialized)))
   {
      std::stringstream error_message;
      error_message << "[Gameplay::set_flat_color_shader]: error: guard \"(!initialized)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("Gameplay::set_flat_color_shader: error: guard \"(!initialized)\" not met");
   }
   this->flat_color_shader = flat_color_shader;
   return;
}

void Gameplay::initialize()
{
   if (!((!initialized)))
   {
      std::stringstream error_message;
      error_message << "[Gameplay::initialize]: error: guard \"(!initialized)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("Gameplay::initialize: error: guard \"(!initialized)\" not met");
   }
   if (!(animation_book))
   {
      std::stringstream error_message;
      error_message << "[Gameplay::initialize]: error: guard \"animation_book\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("Gameplay::initialize: error: guard \"animation_book\" not met");
   }
   if (!(event_emitter))
   {
      std::stringstream error_message;
      error_message << "[Gameplay::initialize]: error: guard \"event_emitter\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("Gameplay::initialize: error: guard \"event_emitter\" not met");
   }
   if (!(flat_color_shader))
   {
      std::stringstream error_message;
      error_message << "[Gameplay::initialize]: error: guard \"flat_color_shader\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("Gameplay::initialize: error: guard \"flat_color_shader\" not met");
   }
   scene_factory.set_animation_book(animation_book);
   scene_factory.set_event_emitter(event_emitter);
   scene_factory.set_flat_color_shader(flat_color_shader);
   scene_factory.initialize();

   initialized = true;
   scene = scene_factory.create_scene_0();
   if (!scene) throw std::runtime_error("Gameplay: scene could not be created");
   return;
}

void Gameplay::primary_timer_func()
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[Gameplay::primary_timer_func]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("Gameplay::primary_timer_func: error: guard \"initialized\" not met");
   }
   if (scene)
   {
      scene->update();
      scene->draw();
   }
}


} // namespace DungeonPlus


