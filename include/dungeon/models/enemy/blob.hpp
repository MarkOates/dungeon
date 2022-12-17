#pragma once


#include <dungeon/models/entities/enemy/base.hpp>
#include <string>


namespace dungeon
{
   namespace models
   {
      namespace enemy
      {
         class blob : public Enemy::Base
         {
         private:
            std::string property;

         protected:


         public:
            blob(std::string property="[unset-property]");
            ~blob();

            std::string get_property() const;
            bool property_is(std::string possible_type="");
         };
      }
   }
}



