


#include <dungeon/models/entities/base.hpp>
#include <dungeon/helpers/scene_collection_helper.hpp>
#include <dungeon/helpers/scene_collision_helper.hpp>
#include <dungeon/models/scene.hpp>
#include <dungeon/entity_attribute_names.hpp>
#include <algorithm>



Scene::Scene(AllegroFlare::EventEmitter *event_emitter, int width)
//Scene::Scene(int width)
   : ElementID(nullptr)
   , event_emitter(event_emitter)
   , floor_min_y(465)
   , floor_max_y(600)
   , width(width)
{
   if (!event_emitter) throw std::runtime_error("Scene no event_emitter");
}



Scene::~Scene()
{
}



void Scene::set_y_bounds(float min_y, float max_y)
{
   floor_min_y = min_y;
   floor_max_y = max_y;
}



void Scene::get_y_bounds(float *min_y, float *max_y)
{
   *min_y = floor_min_y;
   *max_y = floor_max_y;
}



float Scene::get_width()
{
   return width;
}



void Scene::update_all()
{
   SceneCollisionHelper collision_helper(event_emitter, this);
   collision_helper.resolve_collisions();
}



void Scene::cleanup_all()
{
   SceneCollectionHelper collection_helper(this);

   for (auto &descendant : collection_helper.get_all_flagged_for_deletion())
      delete descendant;
}



void Scene::draw_all()
{
   SceneCollectionHelper collection_helper(this);

   std::vector<Entity::Base *> y_sorted_entities = collection_helper.get_all_entities_y_sorted();

   for (auto &entity : y_sorted_entities) if (!entity->exists(ALWAYS_ON_TOP)) entity->draw();
   for (auto &entity : y_sorted_entities) if (entity->exists(ALWAYS_ON_TOP)) entity->draw();
}



