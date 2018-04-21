#pragma once


#include <dungeon/models/entities/enemy/kid_entity.hpp>
#include <dungeon/models/sprite_sheet.hpp>
#include <framework/shader.hpp>


class ElementID;
namespace Entity { class Base; }
class EnemyBase;
class KnightEntity;


class EntityFactory
{
private:
   SpriteSheet character_sprite_sheet;
   Shader flat_color_shader;
   ALLEGRO_BITMAP *background1;
   ALLEGRO_BITMAP *background2;
   ALLEGRO_BITMAP *background3;
   ALLEGRO_BITMAP *background4;
   ALLEGRO_BITMAP *background5;
   ALLEGRO_BITMAP *background6;
   ALLEGRO_BITMAP *door1;
   ALLEGRO_BITMAP *door2;
   ALLEGRO_BITMAP *door3;
   ALLEGRO_BITMAP *door4;
   ALLEGRO_BITMAP *door5;
   ALLEGRO_BITMAP *door6;
   ALLEGRO_BITMAP *club_item;
   std::string reverse_explosion_fx_frames_filename;
   std::string slash_poof_fx_frames_filename;
   static EntityFactory *instance;
   static EntityFactory *get_instance();

   EntityFactory();
   ~EntityFactory();

public:

   // enemies
   static Entity::Base *create_random_kid(ElementID *parent, float x, float y);
   static KidEntity *create_named_kid(ElementID *parent, std::string name, behavior_t behavior, int sprite_index, float x, float y);
   static KnightEntity *create_knight_entity(ElementID *parent, float x, float y);
   static Entity::Base *create_skull_enemy(ElementID *parent, float x, float y, float min_y, float max_y);

   // player
   static Entity::Base *create_krampus(ElementID *parent, float x, float y);

   // damage zones
   static Entity::Base *create_krampus_attack_damage_zone(ElementID *parent, float x, float y, float w, float h);
   static Entity::Base *create_krampus_attack_damage_zone_with_club(ElementID *parent, float x, float y, float w, float h);
   static Entity::Base *create_enemy_attack_damage_zone(ElementID *parent, float x, float y, float w, float h);

   // doors
   static Entity::Base *create_door1(ElementID *parent, float x, float y, std::string name, int destination_scene, std::string destination_door_name);
   static Entity::Base *create_door2(ElementID *parent, float x, float y, std::string name, int destination_scene, std::string destination_door_name);
   static Entity::Base *create_door3(ElementID *parent, float x, float y, std::string name, int destination_scene, std::string destination_door_name);
   static Entity::Base *create_door4(ElementID *parent, float x, float y, std::string name, int destination_scene, std::string destination_door_name);
   static Entity::Base *create_door5(ElementID *parent, float x, float y, std::string name, int destination_scene, std::string destination_door_name);
   static Entity::Base *create_door6(ElementID *parent, float x, float y, std::string name, int destination_scene, std::string destination_door_name);

   // items
   static Entity::Base *create_club_item(ElementID *parent, float x, float y);
   static Entity::Base *create_stone_of_defiance_item(ElementID *parent, float x, float y);
   static Entity::Base *create_naughty_list_item(ElementID *parent, float x, float y);
   static Entity::Base *create_key_item(ElementID *parent, float x, float y);

   // motion fx
   static Entity::Base *create_hit_damage_motion_fx(ElementID *parent, float x, float y, std::string damage_string);
   static Entity::Base *create_reverse_explosion_fx(ElementID *parent, float x, float y);
   static Entity::Base *create_slash_poof_fx(ElementID *parent, float x, float y);

   // backgrounds
   static Entity::Base *create_background1(ElementID *parent, float x, float y);
   static Entity::Base *create_background2(ElementID *parent, float x, float y);
   static Entity::Base *create_background3(ElementID *parent, float x, float y);
   static Entity::Base *create_background4(ElementID *parent, float x, float y);
   static Entity::Base *create_background5(ElementID *parent, float x, float y);
   static Entity::Base *create_background6(ElementID *parent, float x, float y);
};


