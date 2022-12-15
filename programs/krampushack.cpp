


//#include <framework/screens/gamer_input_screen.hpp>
//#include <framework/screen.hpp>
//#include <dungeon/models/audio_controller.hpp>
#include <dungeon/emitters/user_event_emitter.hpp>
#include <dungeon/factories/storyboard_factory.hpp>
#include <dungeon/screens/title_screen.hpp>
#include <dungeon/screens/game_play_screen.hpp>
#include <dungeon/user_events.hpp>


#include <AllegroFlare/VirtualControls.hpp>
#include <AllegroFlare/EventNames.hpp>
#include <AllegroFlare/FontBin.hpp>
#include <AllegroFlare/EventEmitter.hpp>



   //: game_show_music(Framework::sample("game_show_music.ogg"))
   //, storyboard_music(Framework::sample("storyboard_music.ogg"))
   //, haunting_music(Framework::sample("haunting_atmosphere-01.ogg"))
   //, hurt_sound_effect(Framework::sample("217192__rt759__game-voice-3.wav"))
   //, tada_sound_effect(Framework::sample("tada.ogg"))
   //, win_cheer_sound_effect(Framework::sample("win_cheer.ogg"))
   //, strong_punch_sound_effect(Framework::sample("strong_punch.ogg"))
   //, current_music_track_num(-1)
   //, sound_effects()
//{
   //game_show_music.loop(true);
   //storyboard_music.loop(true);
   //haunting_music.loop(true);
//}





class KrampusHackProject : public AllegroFlare::Screens::Base
{
public:
   AllegroFlare::EventEmitter *event_emitter;
   AllegroFlare::BitmapBin *bitmap_bin;
   AllegroFlare::FontBin *font_bin;
   AllegroFlare::Screens::Base *current_screen;
   //AllegroFlare::VirtualControls
   //GamerInputScreen gamer_input_screen; // << -- THIS input screen not working
   //AudioController audio_controller; // TODO: replace this! // TODO: REPLACE THIS

	KrampusHackProject(AllegroFlare::EventEmitter *event_emitter, AllegroFlare::BitmapBin *bitmap_bin, AllegroFlare::FontBin *font_bin)
      //: Screen(display)
      : AllegroFlare::Screens::Base()
      , event_emitter(event_emitter)
      , bitmap_bin(bitmap_bin)
      , font_bin(font_bin)
      , current_screen(nullptr)
      //, audio_controller()
      //, gamer_input_screen()
   {
      if (!event_emitter) throw std::runtime_error("KrampusHackProject:: no event_emitter");
      event_emitter->emit_event(START_TITLE_SCREEN);
      //gamer_input_screen.show_graphic = true;
   }

   void user_event_func(ALLEGRO_EVENT *ev) override
   {
      ALLEGRO_EVENT *event = ev; ////Framework::current_event;

      switch (event->user.type)
      {
      case ALLEGRO_FLARE_EVENT_VIRTUAL_CONTROL_BUTTON_UP:
      //case ALLEGRO_FLARE_EVENT_GAMER_BUTTON_UP:
         //std::cout << "Button RELEASED: " << event->user.data1 << " - " << gamer_input_screen. get_button_name((button_t)event->user.data1) << std::endl;
         break;
      case ALLEGRO_FLARE_EVENT_VIRTUAL_CONTROL_BUTTON_DOWN:
      //case ALLEGRO_EVENT_GAMER_BUTTON_DOWN:
         //std::cout << "Button RELEASED: " << event->user.data1 << " - " << gamer_input_screen. get_button_name((button_t)event->user.data1) << std::endl;
         break;
      case START_TITLE_SCREEN:
         if (current_screen) delete current_screen;
         current_screen = new TitleScreen(event_emitter, font_bin, bitmap_bin->auto_get("sprites_grid-x.png"));
         // audio_controller.play_game_show_music(); // TODO: REPLACE THIS
         break;
      case START_INTRO_STORYBOARD_SCREEN:
         if (current_screen) delete current_screen;
         current_screen = StoryboardFactory::create_opening_storyboard_screen(event_emitter, font_bin->auto_get("ChronoTrigger.ttf 60"));
                  //);
         // audio_controller.play_storyboard_music(); // TODO: REPLACE THIS
         break;
      case START_CLOSING_STORYBOARD_SCREEN:
         if (current_screen) delete current_screen;
         current_screen = StoryboardFactory::create_closing_storyboard_screen(event_emitter, font_bin->auto_get("ChronoTrigger.ttf 60"));
         // audio_controller.play_game_show_music(); // TODO: REPLACE THIS
         break;
      case START_GAME_EVENT:
         delete current_screen;
         current_screen = new GamePlayScreen(event_emitter, bitmap_bin, font_bin); //&gamer_input_screen);
         break;
      case PLAY_MUSIC_TRACK:
         {
            int track_id = event->user.data1;
            // audio_controller.play_audio_track_by_id(track_id);
         }
         break;
      case PLAY_SOUND_EFFECT:
         {
            int sound_effect_id = event->user.data1;
            std::string *track_id_str_ptr = (std::string *)event->user.data2;

            // TODO: REPLACE THIS
            // if (sound_effect_id != 0) audio_controller.play_sound_effect_by_id(sound_effect_id);
            // if (track_id_str_ptr)
            // {
               // audio_controller.play_sound_effect_by_name(*track_id_str_ptr);
               // delete track_id_str_ptr;
            // }
         }
         break;
      case QUIT_GAME_EVENT:
         event_emitter->emit_exit_game_event();
         //AllegroFlare::FrameworksFramework::shutdown_program = true;
         break;
      }
   }
};




#include <AllegroFlare/Frameworks/Full.hpp>
#include <AllegroFlare/Screens/Base.hpp>


//class WrappedKrampusHackProject : public KrampusHackProject, public AllegroFlare::Screens::Base
//{
//public:
   //WrappedKrampusHackProject()
      //: KrampusHackProject(nullptr)
   //{}
   //~WrappedKrampusHackProject() {}
//};



int main(int argc, char **argv)
{
   AllegroFlare::Frameworks::Full framework;
   framework.disable_fullscreen();
   framework.initialize();

   KrampusHackProject wrapped_krampus_hack_project(
         &framework.get_event_emitter_ref(),
         &framework.get_bitmap_bin_ref(),
         &framework.get_font_bin_ref()
      );
   framework.register_screen("wrapped_krampus_hack_project", &wrapped_krampus_hack_project);
   framework.activate_screen("wrapped_krampus_hack_project");
   
   framework.run_loop();

	//Framework::initialize();
	//Display *display = Framework::create_display(1280, 720, ALLEGRO_OPENGL | ALLEGRO_PROGRAMMABLE_PIPELINE);
   //KrampusHackProject *proj = new KrampusHackProject(display);
	//Framework::run_loop();
	return 0;
}



