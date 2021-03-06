


#include <dungeon/models/audio_controller.hpp>

#include <dungeon/music_track_nums.hpp>
#include <framework/framework.hpp>



AudioController::AudioController()
   : game_show_music(Framework::sample("game_show_music.ogg"))
   , storyboard_music(Framework::sample("storyboard_music.ogg"))
   , haunting_music(Framework::sample("haunting_atmosphere-01.ogg"))
   , hurt_sound_effect(Framework::sample("217192__rt759__game-voice-3.wav"))
   , tada_sound_effect(Framework::sample("tada.ogg"))
   , win_cheer_sound_effect(Framework::sample("win_cheer.ogg"))
   , strong_punch_sound_effect(Framework::sample("strong_punch.ogg"))
   , current_music_track_num(-1)
   , sound_effects()
{
   game_show_music.loop(true);
   storyboard_music.loop(true);
   haunting_music.loop(true);
}



AudioController::~AudioController()
{
   stop_all();
   for (auto &sound_effect : sound_effects) delete sound_effect.second;
}



void AudioController::stop_all()
{
   haunting_music.stop();
   storyboard_music.stop();
   game_show_music.stop();
   hurt_sound_effect.stop();
   tada_sound_effect.stop();
   win_cheer_sound_effect.stop();
   strong_punch_sound_effect.stop();
}



void AudioController::play_game_show_music()
{
   play_audio_track_by_id(GAME_SHOW_MUSIC);
}



void AudioController::play_storyboard_music()
{
   play_audio_track_by_id(STORYBOARD_MUSIC);
}



void AudioController::play_haunting_music()
{
   play_audio_track_by_id(HAUNTING_MUSIC);
}



void AudioController::play_hurt_sound_effect()
{
   play_sound_effect_by_id(HURT_SOUND_EFFECT);
}



void AudioController::play_tada_sound_effect()
{
   play_sound_effect_by_id(TADA_SOUND_EFFECT);
}



void AudioController::play_strong_punch_sound_effect()
{
   play_sound_effect_by_id(STRONG_PUNCH_SOUND_EFFECT);
}



void AudioController::play_audio_track_by_id(int track_id)
{
   if (track_id == current_music_track_num) return;

   stop_all();
   current_music_track_num = track_id;

   switch (track_id)
   {
   case GAME_SHOW_MUSIC:
      game_show_music.play();
      break;
   case HAUNTING_MUSIC:
      haunting_music.play();
      break;
   case STORYBOARD_MUSIC:
      storyboard_music.play();
      break;
   default:
      break;
   }
}



void AudioController::play_sound_effect_by_id(int track_id)
{
   switch (track_id)
   {
   case HURT_SOUND_EFFECT:
      hurt_sound_effect.play();
      break;
   case WIN_CHEER_SOUND_EFFECT:
      win_cheer_sound_effect.play();
      break;
   case TADA_SOUND_EFFECT:
      tada_sound_effect.play();
      break;
   case STRONG_PUNCH_SOUND_EFFECT:
      strong_punch_sound_effect.play();
      break;
   default:
      break;
   }
}



void AudioController::play_sound_effect_by_name(std::string id_str)
{
   std::map<std::string, Sound*>::iterator it = sound_effects.find(id_str);
   if (it == sound_effects.end()) sound_effects[id_str] = new Sound(Framework::sample(id_str));

   Sound *sound = sound_effects[id_str];
   if (sound) sound->play();
   else std::cout << "AudioController::play_sound_effect_by_id(std::string id_str) could not play \"" << id_str << "\"" << std::endl;
}



