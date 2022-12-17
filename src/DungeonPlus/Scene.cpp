

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


void Scene::update()
{
   std::vector<DungeonPlus::Sprite*> flat_list_of_entities
      = root.get_flat_list_of_descendants<DungeonPlus::Sprite>();

   for (auto &entity : flat_list_of_entities)
   {
      entity->update();
   }

   return;
}

void Scene::draw()
{
   std::vector<DungeonPlus::Sprite*> entities_y_sorted = get_all_entities_y_sorted();

   for (auto &entity : entities_y_sorted)
   {
      entity->draw();
   }

   return;
}

std::vector<DungeonPlus::Sprite *> Scene::get_all_entities_y_sorted()
{
   std::vector<DungeonPlus::Sprite*> flat_list = root.get_flat_list_of_descendants<DungeonPlus::Sprite>();

   // NOTE: The args in this lamba to be const
   std::sort(flat_list.begin(), flat_list.end(),[](DungeonPlus::Sprite *a, DungeonPlus::Sprite *b)
         { return a->get_place_ref().position.y < b->get_place_ref().position.y; }
      );
   return flat_list;
}


} // namespace DungeonPlus


