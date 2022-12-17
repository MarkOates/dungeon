#pragma once


#include <AllegroFlare/ElementID.hpp>
#include <DungeonPlus/Sprite.hpp>
#include <vector>


namespace DungeonPlus
{
   class Scene
   {
   private:
      AllegroFlare::ElementID root;

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



