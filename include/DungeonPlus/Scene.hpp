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

   protected:


   public:
      Scene();
      ~Scene();

      AllegroFlare::ElementID &get_root_ref();
      void update();
      void draw();
      std::vector<DungeonPlus::Sprite *> get_all_entities_y_sorted();
   };
}



