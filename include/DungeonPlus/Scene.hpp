#pragma once


#include <AllegroFlare/ElementID.hpp>


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
   };
}



