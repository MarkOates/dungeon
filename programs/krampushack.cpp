


#include <framework/screens/gamer_input_screen.hpp>
#include <framework/screen.hpp>
#include <controllers/audio_controller.hpp>
#include <emitters/user_event_emitter.hpp>
#include <factories/storyboard_factory.hpp>
#include <screens/title_screen.hpp>
#include <screens/game_play_screen.hpp>
#include <user_events.hpp>



class KrampusHackProject : public Screen
{
public:
   Screen *current_screen;
   GamerInputScreen gamer_input_screen;
   AudioController audio_controller;

	KrampusHackProject(Display *display)
      : Screen(display)
      , current_screen(nullptr)
      , audio_controller()
      , gamer_input_screen(display)
   {
      UserEventEmitter::emit_event(START_TITLE_SCREEN);
      gamer_input_screen.show_graphic = true;
   }

   void user_event_func() override
   {
      ALLEGRO_EVENT *event = Framework::current_event;

      switch (event->user.type)
      {
      case ALLEGRO_EVENT_GAMER_BUTTON_UP:
         std::cout << "Button RELEASED: " << event->user.data1 << " - " << gamer_input_screen. get_button_name((button_t)event->user.data1) << std::endl;
         break;
      case ALLEGRO_EVENT_GAMER_BUTTON_DOWN:
         std::cout << "Button RELEASED: " << event->user.data1 << " - " << gamer_input_screen. get_button_name((button_t)event->user.data1) << std::endl;
         break;
      case START_TITLE_SCREEN:
         if (current_screen) delete current_screen;
         current_screen = new TitleScreen(display);
         audio_controller.play_game_show_music();
         break;
      case START_INTRO_STORYBOARD_SCREEN:
         if (current_screen) delete current_screen;
         current_screen = StoryboardFactory::create_opening_storyboard_screen(display);
         audio_controller.play_storyboard_music();
         break;
      case START_CLOSING_STORYBOARD_SCREEN:
         if (current_screen) delete current_screen;
         current_screen = StoryboardFactory::create_closing_storyboard_screen(display);
         audio_controller.play_game_show_music();
         break;
      case START_GAME_EVENT:
         delete current_screen;
         current_screen = new GamePlayScreen(display, &gamer_input_screen);
         break;
      case PLAY_MUSIC_TRACK:
         {
            int track_id = event->user.data1;
            audio_controller.play_audio_track_by_id(track_id);
         }
         break;
      case PLAY_SOUND_EFFECT:
         {
            int sound_effect_id = event->user.data1;
            std::string *track_id_str_ptr = (std::string *)event->user.data2;

            if (sound_effect_id != 0) audio_controller.play_sound_effect_by_id(sound_effect_id);
            if (track_id_str_ptr)
            {
               audio_controller.play_sound_effect_by_name(*track_id_str_ptr);
               delete track_id_str_ptr;
            }
         }
         break;
      case QUIT_GAME_EVENT:
         Framework::shutdown_program = true;
         break;
      }
   }
};



int main(int argc, char **argv)
{
	Framework::initialize();
	Display *display = Framework::create_display(1280, 720, ALLEGRO_OPENGL | ALLEGRO_PROGRAMMABLE_PIPELINE);
   KrampusHackProject *proj = new KrampusHackProject(display);
	Framework::run_loop();
	return 0;
}



