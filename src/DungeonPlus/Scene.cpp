

#include <DungeonPlus/Scene.hpp>




namespace DungeonPlus
{


Scene::Scene()
   : root()
   , camera()
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

   camera.size = { 1920, 1080 };
   camera.align = { 0.5, 0.5 };
   camera.position = { 1920/2, 1080/2 };

   for (auto &entity : flat_list_of_entities)
   {
      entity->update();
   }

   return;
}

void Scene::draw()
{
   std::vector<DungeonPlus::Sprite*> entities_y_sorted = get_all_entities_y_sorted();

   //camera.setup_dimentional_projection(al_get_backbuffer(al_get_current_display()));
   camera.start_transform();
   for (auto &entity : entities_y_sorted)
   {
      entity->draw();
   }
   camera.restore_transform();

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


