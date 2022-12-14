

#include <allegro5/allegro.h>
#include <vector>
#include <iostream>


ALLEGRO_EVENT_QUEUE *master_event_queue = nullptr;

#define EVENT_ABORT_PROGRAM ALLEGRO_GET_EVENT_TYPE('A','B','R','T')


class Reciever
{
public:
   ALLEGRO_EVENT_SOURCE event_source;

   Reciever()
   {
      al_init_user_event_source(&event_source);
      al_register_event_source(master_event_queue, &event_source);
   }
   virtual ~Reciever()
   {
      al_unregister_event_source(master_event_queue, &event_source);
   }

   void emit_event(int32_t event_type, intptr_t data1=0, intptr_t data2=0, intptr_t data3=0, intptr_t data4=0)
   {
      ALLEGRO_EVENT al_event;
      al_event.user.type = event_type;
      al_event.user.data1 = data1;
      al_event.user.data2 = data2;
      al_event.user.data3 = data3;
      al_event.user.data4 = data4;
      al_emit_user_event(&event_source, &al_event, NULL);
   }
   virtual void process_event(ALLEGRO_EVENT &event) {}
};


void process_event(ALLEGRO_EVENT &event);


class Project : public Reciever
{
public:
   Project() {}
   void process_event(ALLEGRO_EVENT &event) override
   {
      ::process_event(event);
   }
};




int main(int argc, char **argv)
{
   ALLEGRO_DISPLAY *display = nullptr;
   ALLEGRO_EVENT_SOURCE event_source, *timer_event_source, *keyboard_event_source;
   ALLEGRO_TIMER *timer;
   std::vector<Reciever *> screens;


   if (master_event_queue) throw std::runtime_error("duplicate calling of Framework");
   al_init();
   master_event_queue = al_create_event_queue();
   display = al_create_display(800, 600);
   timer = al_create_timer(ALLEGRO_BPS_TO_SECS(60));

   if (!al_install_keyboard()) throw std::runtime_error("al_install_keyboard() failed.");

   al_init_user_event_source(&event_source);
   keyboard_event_source = al_get_keyboard_event_source();
   timer_event_source = al_get_timer_event_source(timer);
   al_register_event_source(master_event_queue, &event_source);
   al_register_event_source(master_event_queue, timer_event_source);
   al_register_event_source(master_event_queue, keyboard_event_source);


   // create screens here

   Project project;

   screens.push_back(&project);

   // run the loop


   ALLEGRO_EVENT event;
   al_start_timer(timer);
   while (event.type != EVENT_ABORT_PROGRAM)
   {
      al_wait_for_event(master_event_queue, &event);
      bool screen_event = false;
      for (auto &screen : screens)
      {
         screen->process_event(event);
      }

      if (!screen_event)
      {
         if (event.any.source == timer_event_source) for (auto &screen : screens) screen->process_timer_event(event);
         else for (auto &screen : screens) screen->process_global_event(event);
      }
   }

   return 0;
}



