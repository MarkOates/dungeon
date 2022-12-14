#include "thin.h"


void process_event(Event &ev)
{
   switch (ev.type)
   {
   case INITIALIZE:
      register_event_processor(title_screen);
      break;
   }
}


