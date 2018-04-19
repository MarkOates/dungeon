#pragma once


#include <dungeon/models/entities/base.hpp>
#include <framework/display.hpp>
#include <framework/motion.hpp>


class Camera
{
private:
   placement2d place;
   Entity::Base *target;
   ALLEGRO_COLOR overlay_color;
   Motion motion;

public:
   Camera(Display *display, Entity::Base *target);

   void set_target(Entity::Base *new_target=nullptr);

   void update(float max_x);
   void start_transform();
   void restore_transform();
   void set_overlay_color(ALLEGRO_COLOR new_overlay_color);
   void fade_to_black(float duration=0.4);
   void fade_to_clear(float duration=0.4);
   void set_zoom(float scale=1.0);
   void zoom_to(float scale=1.0, float duration=0.4);
   void tilt_to(float tilt, float duration=0.4);

   void draw_overlay();
};


