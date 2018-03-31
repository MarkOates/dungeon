



#include <framework/appearance2d.hpp>

#include <framework/useful.hpp> // for tostring()




appearance2d::appearance2d()
   : color(al_map_rgba_f(1,1,1,1))
   , blender(BLENDER_NORMAL)
   , opacity(1)
{ }




void appearance2d::clear()
{
   color = al_map_rgba_f(1,1,1,1);
   opacity = 1;
   blender = BLENDER_NORMAL;
}




