#ifndef __AF_APPEARANCE_HEADER
#define __AF_APPEARANCE_HEADER




#include <allegro5/allegro.h>
#include <framework/blender.hpp>




class appearance2d
{
public:
   ALLEGRO_COLOR color;
   blender_t blender;
   float opacity;
   // ALLEGRO_SHADER *shader; //< coming soon :o

   appearance2d();
   void clear();
};




#endif
