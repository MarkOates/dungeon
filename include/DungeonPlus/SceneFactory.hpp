#pragma once


#include <AllegroFlare/EventEmitter.hpp>
#include <AllegroFlare/Shader.hpp>
#include <DungeonPlus/AnimationBook.hpp>
#include <DungeonPlus/EntityFactory.hpp>
#include <DungeonPlus/Scene.hpp>


namespace DungeonPlus
{
   class SceneFactory
   {
   private:
      DungeonPlus::AnimationBook* animation_book;
      AllegroFlare::EventEmitter* event_emitter;
      AllegroFlare::Shader* flat_color_shader;
      DungeonPlus::EntityFactory entity_factory;
      bool initialized;

   protected:


   public:
      SceneFactory(DungeonPlus::AnimationBook* animation_book=nullptr, AllegroFlare::EventEmitter* event_emitter=nullptr, AllegroFlare::Shader* flat_color_shader=nullptr);
      ~SceneFactory();

      void set_animation_book(DungeonPlus::AnimationBook* animation_book=nullptr);
      void set_event_emitter(AllegroFlare::EventEmitter* event_emitter=nullptr);
      void set_flat_color_shader(AllegroFlare::Shader* flat_color_shader=nullptr);
      void initialize();
      DungeonPlus::Scene* create_scene_0();
   };
}



