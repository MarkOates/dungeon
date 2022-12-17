#pragma once


#include <AllegroFlare/EventEmitter.hpp>
#include <AllegroFlare/Screens/Base.hpp>
#include <AllegroFlare/Shader.hpp>
#include <DungeonPlus/AnimationBook.hpp>
#include <DungeonPlus/Scene.hpp>
#include <DungeonPlus/SceneFactory.hpp>


namespace DungeonPlus
{
   class Gameplay : public AllegroFlare::Screens::Base
   {
   public:
      static constexpr char* TYPE = (char*)"DungeonPlus/Gameplay";

   private:
      DungeonPlus::AnimationBook* animation_book;
      AllegroFlare::EventEmitter* event_emitter;
      AllegroFlare::Shader* flat_color_shader;
      DungeonPlus::SceneFactory scene_factory;
      DungeonPlus::Scene* scene;
      bool initialized;

   protected:


   public:
      Gameplay(DungeonPlus::AnimationBook* animation_book=nullptr, AllegroFlare::EventEmitter* event_emitter=nullptr, AllegroFlare::Shader* flat_color_shader=nullptr);
      virtual ~Gameplay();

      void set_animation_book(DungeonPlus::AnimationBook* animation_book=nullptr);
      void set_event_emitter(AllegroFlare::EventEmitter* event_emitter=nullptr);
      void set_flat_color_shader(AllegroFlare::Shader* flat_color_shader=nullptr);
      void initialize();
      virtual void primary_timer_func() override;
   };
}



