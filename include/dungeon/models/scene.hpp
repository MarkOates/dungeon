#pragma once


//#include <framework/element_id.hpp>
#include <AllegroFlare/ElementID.hpp>
#include <AllegroFlare/EventEmitter.hpp>


class Scene : public AllegroFlare::ElementID
{
private:
   AllegroFlare::EventEmitter *event_emitter;
   float floor_min_y, floor_max_y;
   float width;

public:
   Scene(AllegroFlare::EventEmitter *event_emitter, int width);
   ~Scene();

   void set_y_bounds(float min_y, float max_y);
   void get_y_bounds(float *min_y, float *max_y);
   float get_width();

   void update_all();
   void cleanup_all();
   void draw_all();
};


