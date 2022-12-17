

#include <DungeonPlus/SceneFactory.hpp>

#include <iostream>
#include <sstream>
#include <stdexcept>


namespace DungeonPlus
{


SceneFactory::SceneFactory(DungeonPlus::AnimationBook* animation_book, AllegroFlare::EventEmitter* event_emitter, AllegroFlare::Shader* flat_color_shader)
   : animation_book(animation_book)
   , event_emitter(event_emitter)
   , flat_color_shader(flat_color_shader)
   , entity_factory()
   , initialized(false)
{
}


SceneFactory::~SceneFactory()
{
}


void SceneFactory::set_animation_book(DungeonPlus::AnimationBook* animation_book)
{
   if (!((!initialized)))
   {
      std::stringstream error_message;
      error_message << "[SceneFactory::set_animation_book]: error: guard \"(!initialized)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("SceneFactory::set_animation_book: error: guard \"(!initialized)\" not met");
   }
   this->animation_book = animation_book;
   return;
}

void SceneFactory::set_event_emitter(AllegroFlare::EventEmitter* event_emitter)
{
   if (!((!initialized)))
   {
      std::stringstream error_message;
      error_message << "[SceneFactory::set_event_emitter]: error: guard \"(!initialized)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("SceneFactory::set_event_emitter: error: guard \"(!initialized)\" not met");
   }
   this->event_emitter = event_emitter;
   return;
}

void SceneFactory::set_flat_color_shader(AllegroFlare::Shader* flat_color_shader)
{
   if (!((!initialized)))
   {
      std::stringstream error_message;
      error_message << "[SceneFactory::set_flat_color_shader]: error: guard \"(!initialized)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("SceneFactory::set_flat_color_shader: error: guard \"(!initialized)\" not met");
   }
   this->flat_color_shader = flat_color_shader;
   return;
}

void SceneFactory::initialize()
{
   if (!((!initialized)))
   {
      std::stringstream error_message;
      error_message << "[SceneFactory::initialize]: error: guard \"(!initialized)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("SceneFactory::initialize: error: guard \"(!initialized)\" not met");
   }
   if (!(animation_book))
   {
      std::stringstream error_message;
      error_message << "[SceneFactory::initialize]: error: guard \"animation_book\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("SceneFactory::initialize: error: guard \"animation_book\" not met");
   }
   if (!(event_emitter))
   {
      std::stringstream error_message;
      error_message << "[SceneFactory::initialize]: error: guard \"event_emitter\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("SceneFactory::initialize: error: guard \"event_emitter\" not met");
   }
   if (!(flat_color_shader))
   {
      std::stringstream error_message;
      error_message << "[SceneFactory::initialize]: error: guard \"flat_color_shader\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("SceneFactory::initialize: error: guard \"flat_color_shader\" not met");
   }
   entity_factory.set_animation_book(animation_book);
   entity_factory.set_event_emitter(event_emitter);
   entity_factory.set_flat_color_shader(flat_color_shader);
   entity_factory.initialize();

   initialized = true;
   return;
}

DungeonPlus::Scene* SceneFactory::create_scene_0()
{
   DungeonPlus::Scene* scene = new DungeonPlus::Scene();
   entity_factory.set_scene(scene);

   entity_factory.create_blob(1920 / 2, 1080 / 2);
   entity_factory.create_blob(1920 / 2 + 200, 1080 / 2);
   entity_factory.create_blob(1920 / 2 - 200, 1080 / 2);

   return nullptr;
}


} // namespace DungeonPlus


