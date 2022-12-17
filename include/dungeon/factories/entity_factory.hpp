#pragma once


#include <dungeon/models/entities/enemy/kid_entity.hpp>
#include <dungeon/models/sprite_sheet.hpp>
//#include <framework/shader.hpp>
#include <AllegroFlare/Shader.hpp>
//#include <AllegroFlare/ElementID.hpp>
#include <AllegroFlare/BitmapBin.hpp>
#include <AllegroFlare/FontBin.hpp>
#include <AllegroFlare/EventEmitter.hpp>
#include <DungeonPlus/AnimationBook.hpp>


namespace AllegroFlare { class ElementID; }
namespace Entity { class Base; }
class EnemyBase;
class KnightEntity;


class EntityFactory
{
private:
   SpriteSheet character_sprite_sheet;
   AllegroFlare::Shader *flat_color_shader;
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
   ALLEGRO_BITMAP *reverse_explosion_fx_frames_bitmap;
   std::string slash_poof_fx_frames_filename;
   ALLEGRO_BITMAP *slash_poof_fx_frames_bitmap;
   AllegroFlare::FontBin *font_bin;
   AllegroFlare::EventEmitter *event_emitter;
   DungeonPlus::AnimationBook *animation_book;

   static EntityFactory *instance;
   static EntityFactory *get_instance();
   static bool initialized;
   static AllegroFlare::Random random;

   EntityFactory(AllegroFlare::Shader *flat_color_shader, AllegroFlare::EventEmitter *event_emitter, AllegroFlare::BitmapBin *bitmap_bin, AllegroFlare::FontBin *font_bin, ALLEGRO_BITMAP *sprites_grid_bitmap, DungeonPlus::AnimationBook *animation_book);
   ~EntityFactory();

public:


   static void init(AllegroFlare::Shader *flat_color_shader, AllegroFlare::EventEmitter *event_emitter, AllegroFlare::BitmapBin *bitmap_bin, AllegroFlare::FontBin *font_bin, ALLEGRO_BITMAP *sprites_grid_bitmap, DungeonPlus::AnimationBook *animation_book);

   ALLEGRO_BITMAP *create_pixel_perfect_scaled_render(ALLEGRO_BITMAP *bitmap, float scale);


   static Entity::Base *create_random_kid(AllegroFlare::ElementID *parent, float x, float y);
   static KidEntity *create_named_kid(AllegroFlare::ElementID *parent, std::string name, behavior_t behavior, int sprite_index, float x, float y);
   static KnightEntity *create_knight_entity(AllegroFlare::ElementID *parent, float x, float y);
   static Entity::Base *create_skull_enemy(AllegroFlare::ElementID *parent, float x, float y, float min_y, float max_y);
   static Entity::Base *create_krampus(AllegroFlare::ElementID *parent, float x, float y);
   static Entity::Base *create_krampus_attack_damage_zone(AllegroFlare::ElementID *parent, float x, float y, float w, float h);
   static Entity::Base *create_krampus_attack_damage_zone_with_club(AllegroFlare::ElementID *parent, float x, float y, float w, float h);
   static Entity::Base *create_enemy_attack_damage_zone(AllegroFlare::ElementID *parent, float x, float y, float w, float h);
   static Entity::Base *create_door1(AllegroFlare::ElementID *parent, float x, float y, std::string name, int destination_scene, std::string destination_door_name);
   static Entity::Base *create_door2(AllegroFlare::ElementID *parent, float x, float y, std::string name, int destination_scene, std::string destination_door_name);
   static Entity::Base *create_door3(AllegroFlare::ElementID *parent, float x, float y, std::string name, int destination_scene, std::string destination_door_name);
   static Entity::Base *create_door4(AllegroFlare::ElementID *parent, float x, float y, std::string name, int destination_scene, std::string destination_door_name);
   static Entity::Base *create_door5(AllegroFlare::ElementID *parent, float x, float y, std::string name, int destination_scene, std::string destination_door_name);
   static Entity::Base *create_door6(AllegroFlare::ElementID *parent, float x, float y, std::string name, int destination_scene, std::string destination_door_name);
   static Entity::Base *create_club_item(AllegroFlare::ElementID *parent, float x, float y);
   static Entity::Base *create_stone_of_defiance_item(AllegroFlare::ElementID *parent, float x, float y);
   static Entity::Base *create_naughty_list_item(AllegroFlare::ElementID *parent, float x, float y);
   static Entity::Base *create_key_item(AllegroFlare::ElementID *parent, float x, float y);
   static Entity::Base *create_hit_damage_motion_fx(AllegroFlare::ElementID *parent, float x, float y, std::string damage_string);
   static Entity::Base *create_reverse_explosion_fx(AllegroFlare::ElementID *parent, float x, float y);
   static Entity::Base *create_slash_poof_fx(AllegroFlare::ElementID *parent, float x, float y);

   static Entity::Base *create_background1(AllegroFlare::ElementID *parent, float x, float y);
   static Entity::Base *create_background2(AllegroFlare::ElementID *parent, float x, float y);
   static Entity::Base *create_background3(AllegroFlare::ElementID *parent, float x, float y);
   static Entity::Base *create_background4(AllegroFlare::ElementID *parent, float x, float y);
   static Entity::Base *create_background5(AllegroFlare::ElementID *parent, float x, float y);
   static Entity::Base *create_background6(AllegroFlare::ElementID *parent, float x, float y);
};


