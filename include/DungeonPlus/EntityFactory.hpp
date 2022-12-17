#pragma once


#include <AllegroFlare/EventEmitter.hpp>
#include <AllegroFlare/Shader.hpp>
#include <DungeonPlus/AnimationBook.hpp>
#include <DungeonPlus/Scene.hpp>
#include <DungeonPlus/Sprite.hpp>


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
      DungeonPlus::Sprite* create_sprite();

   protected:


   public:
      EntityFactory(DungeonPlus::AnimationBook* animation_book=nullptr, AllegroFlare::EventEmitter* event_emitter=nullptr, AllegroFlare::Shader* flat_color_shader=nullptr, DungeonPlus::Scene* scene=nullptr);
      ~EntityFactory();

      void set_scene(DungeonPlus::Scene* scene);
      void initialize();
      DungeonPlus::Sprite* create_blob();
   };
}



