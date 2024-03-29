#pragma once


#include <AllegroFlare/EventEmitter.hpp>
#include <AllegroFlare/Shader.hpp>
#include <DungeonPlus/AnimationBook.hpp>
#include <DungeonPlus/Scene.hpp>
#include <DungeonPlus/Sprite.hpp>
#include <string>


namespace DungeonPlus
{
   class EntityFactory
   {
   private:
      DungeonPlus::AnimationBook* animation_book;
      AllegroFlare::EventEmitter* event_emitter;
      AllegroFlare::Shader* flat_color_shader;
      DungeonPlus::Scene* scene;
      bool initialized;
      DungeonPlus::Sprite* create_sprite(float x=0.0f, float y=0.0f, float w=0.0f, float h=0.0f, std::string type="[unset-type]");

   protected:


   public:
      EntityFactory(DungeonPlus::AnimationBook* animation_book=nullptr, AllegroFlare::EventEmitter* event_emitter=nullptr, AllegroFlare::Shader* flat_color_shader=nullptr, DungeonPlus::Scene* scene=nullptr);
      ~EntityFactory();

      void set_scene(DungeonPlus::Scene* scene);
      void set_animation_book(DungeonPlus::AnimationBook* animation_book=nullptr);
      void set_event_emitter(AllegroFlare::EventEmitter* event_emitter=nullptr);
      void set_flat_color_shader(AllegroFlare::Shader* flat_color_shader=nullptr);
      void initialize();
      DungeonPlus::Sprite* create_blob(float x=0.0f, float y=0.0f);
   };
}



