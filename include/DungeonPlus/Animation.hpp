#pragma once


#include <DungeonPlus/AnimationFrame.hpp>
#include <allegro5/allegro.h>
#include <cstdint>
#include <dungeon/models/sprite_sheet.hpp>
#include <string>
#include <vector>


namespace DungeonPlus
{
   class Animation
   {
   public:
      static constexpr uint32_t PLAYMODE_UNDEF = 0;
      static constexpr uint32_t PLAYMODE_FORWARD_ONCE = 1;
      static constexpr uint32_t PLAYMODE_FORWARD_LOOP = 2;
      static constexpr uint32_t PLAYMODE_FORWARD_PING_PONG = 3;

   private:
      SpriteSheet* sprite_sheet;
      std::string name;
      std::vector<AnimationFrame> frames;
      uint32_t playmode;
      float playhead;
      bool finished;
      bool initialized;

   protected:


   public:
      Animation(SpriteSheet* sprite_sheet=nullptr, std::string name="[unset-name]", std::vector<AnimationFrame> frames={}, uint32_t playmode=PLAYMODE_UNDEF);
      ~Animation();

      std::vector<AnimationFrame> get_frames() const;
      uint32_t get_playmode() const;
      void initialize();
      void start();
      void update();
      void draw();
      int get_num_frames();
      ALLEGRO_BITMAP* get_frame_now();
      ALLEGRO_BITMAP* get_bitmap_at_frame_num(int frame_num=0);
      uint32_t get_frame_id_now();
      uint32_t get_frame_id_at(float time=0.0f);
      ALLEGRO_BITMAP* get_frame_at(float time=0.0f);
      float calculate_duration();
   };
}



