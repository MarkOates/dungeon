



#include <AllegroFlare/InteractiveDevelopment.hpp>


#include <dungeon/models/camera.hpp>

#include <allegro5/allegro_primitives.h>
#include <AllegroFlare/Color.hpp>

//using AllegroFlare::color::color;



Camera::Camera(Entity::Base *target)
   : place(0, 0, 1920, 1080)
   , target(target)
   , overlay_color(AllegroFlare::color::transparent)
   , motion()
   , world_height(144*5)
{}



void Camera::set_target(Entity::Base *new_target)
{
   target = new_target;
}




void Camera::update(float max_x)
{
   motion.update(al_get_time());

   if (debugger_active)
   {
      debugger_active = false;
   }



   float right_camera_edge = max_x-place.size.y/2;
   float left_camera_edge = 0;



   if (target) place.position.x = target->place.position.x;
   place.position.y = (int)(world_height * 0.5);



   float this_cameras_left_edge = place.position.x - place.size.x/2;
   float this_cameras_right_edge = place.position.x + place.size.x/2;
   float screen_size = max_x;

   if (screen_size < place.size.x) place.position.x = max_x * 0.5;
   else if (place.position.x < place.size.x/2) place.position.x = place.size.x/2;
   else if (place.position.x > right_camera_edge) place.position.x = right_camera_edge;
}



void Camera::start_transform()
{
   place.start_reverse_transform();
}



void Camera::restore_transform()
{
   place.restore_transform();
}



void Camera::draw_overlay()
{
   al_draw_filled_rectangle(0, 0, place.size.x, place.size.y, overlay_color);
}



void Camera::set_overlay_color(ALLEGRO_COLOR new_overlay_color)
{
   overlay_color = new_overlay_color;

   motion.clear_animations_on(&overlay_color.r);
   motion.clear_animations_on(&overlay_color.g);
   motion.clear_animations_on(&overlay_color.b);
   motion.clear_animations_on(&overlay_color.a);
}



void Camera::fade_to_black(float duration)
{
   motion.cmove_to(&overlay_color.r, 0, duration);
   motion.cmove_to(&overlay_color.g, 0, duration);
   motion.cmove_to(&overlay_color.b, 0, duration);
   motion.cmove_to(&overlay_color.a, 1.0, duration);
}



void Camera::fade_to_clear(float duration)
{
   motion.cmove_to(&overlay_color.r, 0, duration);
   motion.cmove_to(&overlay_color.g, 0, duration);
   motion.cmove_to(&overlay_color.b, 0, duration);
   motion.cmove_to(&overlay_color.a, 0, duration);
}



void Camera::set_zoom(float scale)
{
   //scale -= 0.0;
   place.scale.x = scale;
   place.scale.y = scale;
}



void Camera::zoom_to(float scale, float duration)
{
   //scale -= 0.0;
   motion.cmove_to(&place.scale.x, scale, duration);
   motion.cmove_to(&place.scale.y, scale, duration);
}



void Camera::tilt_to(float tilt, float duration)
{
   motion.cmove_to(&place.rotation, tilt, duration);
}



