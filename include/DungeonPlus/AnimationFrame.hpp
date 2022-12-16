#pragma once




namespace DungeonPlus
{
   class AnimationFrame
   {
   private:
      int index;
      float duration;

   protected:


   public:
      AnimationFrame(int index=0, float duration=200);
      ~AnimationFrame();

      float get_duration() const;
   };
}



