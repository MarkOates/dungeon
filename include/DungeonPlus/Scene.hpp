#pragma once


#include <AllegroFlare/Camera2D.hpp>
#include <AllegroFlare/ElementID.hpp>
#include <DungeonPlus/Sprite.hpp>
#include <vector>


namespace DungeonPlus
{
   class Scene
   {
   private:
      AllegroFlare::ElementID root;
      AllegroFlare::Camera2D camera;
      DungeonPlus::Sprite* camera_following_entity;

   protected:


   public:
      Scene();
      ~Scene();

      AllegroFlare::ElementID &get_root_ref();
      void set_camera_following_entity(DungeonPlus::Sprite* sprite=nullptr);
      void update();
      void draw();
      std::vector<DungeonPlus::Sprite *> get_all_entities_y_sorted();
   };
}



