


#include <dungeon/factories/entity_factory.hpp>

//#include <framework/framework.hpp>
//#include <framework/image_processing.hpp>
#include <dungeon/models/entities/motion_fx/frame_animation.hpp>
#include <dungeon/models/entities/motion_fx/hit_damage.hpp>
#include <dungeon/models/entities/enemy/base.hpp>
#include <dungeon/models/entities/enemy/knight_entity.hpp>
#include <dungeon/models/entities/enemy/Skull.hpp>
#include <dungeon/models/entities/enemy/blob.hpp>
#include <dungeon/models/entities/background_entity.hpp>
#include <dungeon/models/entities/door_entity.hpp>
#include <dungeon/models/entities/damage_zone_entity.hpp>
#include <dungeon/models/entities/item_entity.hpp>
#include <dungeon/models/entities/krampus_entity.hpp>
#include <dungeon/item_type_nums.hpp>

#include <AllegroFlare/ImageProcessing.hpp>



EntityFactory *EntityFactory::get_instance()
{
   if (!initialized) throw std::runtime_error("EntityFactory not initialized A");

   //if (!instance) instance = new EntityFactory();
   return instance;
}



void EntityFactory::init(AllegroFlare::Shader *flat_color_shader, AllegroFlare::EventEmitter *event_emitter, AllegroFlare::BitmapBin *bitmap_bin, AllegroFlare::FontBin *font_bin, ALLEGRO_BITMAP *sprites_grid_bitmap, DungeonPlus::AnimationBook *animation_book)
{
   if (!instance)
   {
      instance = new EntityFactory(flat_color_shader, event_emitter, bitmap_bin, font_bin, sprites_grid_bitmap, animation_book);
      initialized = true;
   }
   //if (!instance) instance = new EntityFactory();
   //return instance;
}



EntityFactory::EntityFactory(AllegroFlare::Shader *flat_color_shader, AllegroFlare::EventEmitter *event_emitter, AllegroFlare::BitmapBin *bitmap_bin, AllegroFlare::FontBin *font_bin, ALLEGRO_BITMAP *sprites_grid_bitmap, DungeonPlus::AnimationBook *animation_book)
   : character_sprite_sheet(sprites_grid_bitmap, SPRITES_GRID_SPRITE_WIDTH, SPRITES_GRID_SPRITE_HEIGHT, SPRITES_GRID_SPRITE_SCALING)
   , flat_color_shader(flat_color_shader)
   //, flat_color_shader("data/shaders/flat_color_shader.vertex.glsl", "data/shaders/flat_color_shader.fragment.glsl")
   //, flat_color_shader("flat_color_shader", "data/shaders/flat_color_shader.vertex.glsl", "data/shaders/flat_color_shader.fragment.glsl")
   , background1(nullptr)
   , background2(nullptr)
   , background3(nullptr)
   , background4(nullptr)
   , background5(nullptr)
   , background6(nullptr)
   , door1(nullptr)
   , door2(nullptr)
   , door3(nullptr)
   , door4(nullptr)
   , door5(nullptr)
   , door6(nullptr)
   , reverse_explosion_fx_frames_filename("reverse_explosion.png")
   , reverse_explosion_fx_frames_bitmap(nullptr)
   , slash_poof_fx_frames_filename("slash_poof_fx.png")
   , slash_poof_fx_frames_bitmap(nullptr)
   , font_bin(font_bin)
   , event_emitter(event_emitter)
   , animation_book(animation_book)
{
   if (!bitmap_bin) throw std::runtime_error("EntityFactory no bitmap_bin");
   if (!font_bin) throw std::runtime_error("EntityFactory no font_bin");
   if (!event_emitter) throw std::runtime_error("EntityFactory no event_emitter");
   if (!flat_color_shader) throw std::runtime_error("EntityFactory no flat_color_shader");
   if (!animation_book) throw std::runtime_error("EntityFactory no animation_book");

   background1 = create_pixel_perfect_scaled_render(bitmap_bin->auto_get("background-1-08.png"), 5);
   background2 = create_pixel_perfect_scaled_render(bitmap_bin->auto_get("background-2-02.png"), 5);
   background3 = create_pixel_perfect_scaled_render(bitmap_bin->auto_get("background-3-02b.png"), 5);
   background4 = create_pixel_perfect_scaled_render(bitmap_bin->auto_get("background-4-01.png"), 5);
   background5 = create_pixel_perfect_scaled_render(bitmap_bin->auto_get("background-5-01.png"), 5);
   background6 = create_pixel_perfect_scaled_render(bitmap_bin->auto_get("background-6-02.png"), 5);
   door1 = create_pixel_perfect_scaled_render(bitmap_bin->auto_get("door-1-02.png"), 5);
   door2 = create_pixel_perfect_scaled_render(bitmap_bin->auto_get("door-2-01.png"), 5);
   door3 = create_pixel_perfect_scaled_render(bitmap_bin->auto_get("door-3-01.png"), 5);
   door4 = create_pixel_perfect_scaled_render(bitmap_bin->auto_get("door-4-01.png"), 5);
   door5 = create_pixel_perfect_scaled_render(bitmap_bin->auto_get("door-5-01.png"), 5);
   door6 = create_pixel_perfect_scaled_render(bitmap_bin->auto_get("door-6-01.png"), 5);

   slash_poof_fx_frames_bitmap = bitmap_bin->auto_get(slash_poof_fx_frames_filename);
   reverse_explosion_fx_frames_bitmap = bitmap_bin->auto_get(reverse_explosion_fx_frames_filename);
}



ALLEGRO_BITMAP *EntityFactory::create_pixel_perfect_scaled_render(ALLEGRO_BITMAP *bitmap, float scale)
{
   //if (!initialized) throw std::runtime_error("EntityFactory not initialized B");

   AllegroFlare::ImageProcessing image_processing(bitmap);
   return image_processing.create_pixel_perfect_scaled_render(scale);
}



Entity::Base *EntityFactory::create_blob(AllegroFlare::ElementID *parent, float x, float y)
{
   if (!initialized) throw std::runtime_error("EntityFactory not initialized N");
   Blob *result = new Blob(
         parent,
         get_instance()->event_emitter,
         &get_instance()->character_sprite_sheet,
         get_instance()->flat_color_shader,
         x,
         y,
         "blob"
      );
   return result;
}




Entity::Base *EntityFactory::create_random_kid(AllegroFlare::ElementID *parent, float x, float y)
{
   if (!initialized) throw std::runtime_error("EntityFactory not initialized C");

   behavior_t behavior = (behavior_t)random.get_random_int(BEHAVIOR_ADULT, BEHAVIOR_NICE);
   return new KidEntity(parent, get_instance()->event_emitter, &get_instance()->character_sprite_sheet, get_instance()->flat_color_shader, x, y, "[random name]", behavior, -1, -1);
}



KidEntity *EntityFactory::create_named_kid(AllegroFlare::ElementID *parent, std::string name, behavior_t behavior, int sprite_index, float x, float y)
{
   if (!initialized) throw std::runtime_error("EntityFactory not initialized D");

   int identity_sprite_index = 29;
   if (behavior == BEHAVIOR_NAUGHTY) identity_sprite_index = 28;
   else if (behavior == BEHAVIOR_NICE) identity_sprite_index = 27;
   return new KidEntity(parent, get_instance()->event_emitter, &get_instance()->character_sprite_sheet, get_instance()->flat_color_shader, x, y, name, behavior, sprite_index, identity_sprite_index);
}



KnightEntity *EntityFactory::create_knight_entity(AllegroFlare::ElementID *parent, float x, float y)
{
   if (!initialized) throw std::runtime_error("EntityFactory not initialized E");

   return new KnightEntity(parent, get_instance()->event_emitter, &get_instance()->character_sprite_sheet, get_instance()->flat_color_shader, x, y, "Harold", knight_behavior_t::BEHAVIOR_NORMAL, 32, -1);
}



Entity::Base *EntityFactory::create_skull_enemy(AllegroFlare::ElementID *parent,float x, float y, float min_y, float max_y)
{
   if (!initialized) throw std::runtime_error("EntityFactory not initialized F");

   return new Enemy::Skull(parent, get_instance()->animation_book, get_instance()->event_emitter, &get_instance()->character_sprite_sheet, x, y, min_y, max_y);
}



Entity::Base *EntityFactory::create_krampus(AllegroFlare::ElementID *parent, float x, float y)
{
   if (!initialized) throw std::runtime_error("EntityFactory not initialized G");

   return new KrampusEntity(parent, get_instance()->event_emitter, &get_instance()->character_sprite_sheet, get_instance()->animation_book, x, y);
}



Entity::Base *EntityFactory::create_krampus_attack_damage_zone(AllegroFlare::ElementID *parent, float x, float y, float w, float h)
{
   if (!initialized) throw std::runtime_error("EntityFactory not initialized H");

   return new DamageZoneEntity(parent, "krampus_damage_zone", false, true, x, y, w, h);
}



Entity::Base *EntityFactory::create_krampus_attack_damage_zone_with_club(AllegroFlare::ElementID *parent, float x, float y, float w, float h)
{
   if (!initialized) throw std::runtime_error("EntityFactory not initialized");

   return new DamageZoneEntity(parent, "krampus_damage_zone_club", false, true, x, y, w, h);
}



Entity::Base *EntityFactory::create_enemy_attack_damage_zone(AllegroFlare::ElementID *parent, float x, float y, float w, float h)
{
   if (!initialized) throw std::runtime_error("EntityFactory not initialized");

   return new DamageZoneEntity(parent, "enemy_attack_damage_zone", true, false, x, y, w, h);
}



Entity::Base *EntityFactory::create_background1(AllegroFlare::ElementID *parent, float x, float y)
{
   if (!initialized) throw std::runtime_error("EntityFactory not initialized");

   return new BackgroundEntity(parent, get_instance()->background1, x, y);
}



Entity::Base *EntityFactory::create_background2(AllegroFlare::ElementID *parent, float x, float y)
{
   if (!initialized) throw std::runtime_error("EntityFactory not initialized");

   return new BackgroundEntity(parent, get_instance()->background2, x, y);
}



Entity::Base *EntityFactory::create_background3(AllegroFlare::ElementID *parent, float x, float y)
{
   if (!initialized) throw std::runtime_error("EntityFactory not initialized");

   return new BackgroundEntity(parent, get_instance()->background3, x, y);
}



Entity::Base *EntityFactory::create_background4(AllegroFlare::ElementID *parent, float x, float y)
{
   if (!initialized) throw std::runtime_error("EntityFactory not initialized");

   return new BackgroundEntity(parent, get_instance()->background4, x, y);
}



Entity::Base *EntityFactory::create_background5(AllegroFlare::ElementID *parent, float x, float y)
{
   if (!initialized) throw std::runtime_error("EntityFactory not initialized");

   return new BackgroundEntity(parent, get_instance()->background5, x, y);
}



Entity::Base *EntityFactory::create_background6(AllegroFlare::ElementID *parent, float x, float y)
{
   if (!initialized) throw std::runtime_error("EntityFactory not initialized");

   return new BackgroundEntity(parent, get_instance()->background6, x, y);
}



Entity::Base *EntityFactory::create_door1(AllegroFlare::ElementID *parent, float x, float y, std::string name, int destination_scene, std::string destination_door_name)
{
   if (!initialized) throw std::runtime_error("EntityFactory not initialized");

   return new DoorEntity(parent, name, destination_scene, destination_door_name, get_instance()->door1, x, y);
}



Entity::Base *EntityFactory::create_door2(AllegroFlare::ElementID *parent, float x, float y, std::string name, int destination_scene, std::string destination_door_name)
{
   if (!initialized) throw std::runtime_error("EntityFactory not initialized");

   return new DoorEntity(parent, name, destination_scene, destination_door_name, get_instance()->door2, x, y);
}



Entity::Base *EntityFactory::create_door3(AllegroFlare::ElementID *parent, float x, float y, std::string name, int destination_scene, std::string destination_door_name)
{
   if (!initialized) throw std::runtime_error("EntityFactory not initialized");

   return new DoorEntity(parent, name, destination_scene, destination_door_name, get_instance()->door3, x, y);
}



Entity::Base *EntityFactory::create_door4(AllegroFlare::ElementID *parent, float x, float y, std::string name, int destination_scene, std::string destination_door_name)
{
   if (!initialized) throw std::runtime_error("EntityFactory not initialized");

   return new DoorEntity(parent, name, destination_scene, destination_door_name, get_instance()->door4, x, y);
}



Entity::Base *EntityFactory::create_door5(AllegroFlare::ElementID *parent, float x, float y, std::string name, int destination_scene, std::string destination_door_name)
{
   if (!initialized) throw std::runtime_error("EntityFactory not initialized");

   return new DoorEntity(parent, name, destination_scene, destination_door_name, get_instance()->door5, x, y);
}



Entity::Base *EntityFactory::create_door6(AllegroFlare::ElementID *parent, float x, float y, std::string name, int destination_scene, std::string destination_door_name)
{
   if (!initialized) throw std::runtime_error("EntityFactory not initialized");

   return new DoorEntity(parent, name, destination_scene, destination_door_name, get_instance()->door6, x, y);
}



Entity::Base *EntityFactory::create_club_item(AllegroFlare::ElementID *parent, float x, float y)
{
   if (!initialized) throw std::runtime_error("EntityFactory not initialized");

   return new ItemEntity(parent, get_instance()->character_sprite_sheet.get_sprite(23), ITEM_TYPE_CLUB, x, y);
}



Entity::Base *EntityFactory::create_stone_of_defiance_item(AllegroFlare::ElementID *parent, float x, float y)
{
   if (!initialized) throw std::runtime_error("EntityFactory not initialized");

   return new ItemEntity(parent, get_instance()->character_sprite_sheet.get_sprite(24), ITEM_TYPE_STONE_OF_DEFIANCE, x, y);
}



Entity::Base *EntityFactory::create_naughty_list_item(AllegroFlare::ElementID *parent, float x, float y)
{
   if (!initialized) throw std::runtime_error("EntityFactory not initialized");

   return new ItemEntity(parent, get_instance()->character_sprite_sheet.get_sprite(25), ITEM_TYPE_NAUGHTY_LIST, x, y);
}



Entity::Base *EntityFactory::create_key_item(AllegroFlare::ElementID *parent, float x, float y)
{
   if (!initialized) throw std::runtime_error("EntityFactory not initialized");

   return new ItemEntity(parent, get_instance()->character_sprite_sheet.get_sprite(26), ITEM_TYPE_KEY, x, y);
}



Entity::Base *EntityFactory::create_hit_damage_motion_fx(AllegroFlare::ElementID *parent, float x, float y, std::string damage_string)
{
   if (!initialized) throw std::runtime_error("EntityFactory not initialized");

   //get_instance()->font_bin->auto_get("ChronoTrigger.ttf 20"), 

   return new MotionFX::HitDamage(parent, get_instance()->font_bin->auto_get("ChronoTrigger.ttf 20"), x, y, damage_string);
}



Entity::Base *EntityFactory::create_slash_poof_fx(AllegroFlare::ElementID *parent, float x, float y)
{
   if (!initialized) throw std::runtime_error("EntityFactory not initialized");

   MotionFX::FrameAnimation *frame_animation = new MotionFX::FrameAnimation(parent, get_instance()->slash_poof_fx_frames_bitmap, 48, 48, 5, x, y);
   frame_animation->set_frames_per_second(20.0);
   return frame_animation;
}



Entity::Base *EntityFactory::create_reverse_explosion_fx(AllegroFlare::ElementID *parent, float x, float y)
{
   if (!initialized) throw std::runtime_error("EntityFactory not initialized");

   MotionFX::FrameAnimation *frame_animation = new MotionFX::FrameAnimation(parent, get_instance()->reverse_explosion_fx_frames_bitmap, 64, 64, 5, x, y);
   return frame_animation;
}



EntityFactory *EntityFactory::instance = nullptr;
bool EntityFactory::initialized = false;
AllegroFlare::Random EntityFactory::random;
//AllegroFlare::FontBin *EntityFactory::font_bin = nullptr




