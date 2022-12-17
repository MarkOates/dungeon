

#include <DungeonPlus/EntityFactory.hpp>

#include <iostream>
#include <sstream>
#include <stdexcept>


namespace DungeonPlus
{


EntityFactory::EntityFactory(DungeonPlus::AnimationBook* animation_book, AllegroFlare::EventEmitter* event_emitter, AllegroFlare::Shader* flat_color_shader, DungeonPlus::Scene* scene)
   : animation_book(animation_book)
   , event_emitter(event_emitter)
   , flat_color_shader(flat_color_shader)
   , scene(scene)
   , initialized(false)
{
}


EntityFactory::~EntityFactory()
{
}


void EntityFactory::set_scene(DungeonPlus::Scene* scene)
{
   this->scene = scene;
}


void EntityFactory::initialize()
{
   if (!((!initialized)))
   {
      std::stringstream error_message;
      error_message << "[EntityFactory::initialize]: error: guard \"(!initialized)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("EntityFactory::initialize: error: guard \"(!initialized)\" not met");
   }
   if (!(animation_book))
   {
      std::stringstream error_message;
      error_message << "[EntityFactory::initialize]: error: guard \"animation_book\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("EntityFactory::initialize: error: guard \"animation_book\" not met");
   }
   if (!(event_emitter))
   {
      std::stringstream error_message;
      error_message << "[EntityFactory::initialize]: error: guard \"event_emitter\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("EntityFactory::initialize: error: guard \"event_emitter\" not met");
   }
   if (!(flat_color_shader))
   {
      std::stringstream error_message;
      error_message << "[EntityFactory::initialize]: error: guard \"flat_color_shader\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("EntityFactory::initialize: error: guard \"flat_color_shader\" not met");
   }
   initialized = true;
   return;
}

DungeonPlus::Sprite* EntityFactory::create_blob()
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[EntityFactory::create_blob]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("EntityFactory::create_blob: error: guard \"initialized\" not met");
   }
   DungeonPlus::Sprite *sprite = create_sprite();
   sprite->set("type", "blob");
   return sprite;
}

DungeonPlus::Sprite* EntityFactory::create_sprite()
{
   if (!(scene))
   {
      std::stringstream error_message;
      error_message << "[EntityFactory::create_sprite]: error: guard \"scene\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("EntityFactory::create_sprite: error: guard \"scene\" not met");
   }
   DungeonPlus::Sprite *sprite = new DungeonPlus::Sprite(animation_book, event_emitter, flat_color_shader);
   sprite->reassign_parent(scene);
   sprite->initialize();
   return sprite;
}


} // namespace DungeonPlus


