

#include <DungeonPlus/Scene.hpp>




namespace DungeonPlus
{


Scene::Scene()
   : root()
{
}


Scene::~Scene()
{
}


AllegroFlare::ElementID &Scene::get_root_ref()
{
   return root;
}




} // namespace DungeonPlus


