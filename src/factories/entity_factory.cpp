


#include <framework/framework.hpp>
#include <framework/image_processing.hpp>
#include <factories/entity_factory.hpp>
#include <models/entities/motion_fx/motion_fx_hit_damage.hpp>
#include <models/entities/enemies/knight_entity.hpp>
#include <models/entities/enemies/kid_entity.hpp>
#include <models/entities/enemies/enemy_base.hpp>
#include <models/entities/background_entity.hpp>
#include <models/entities/door_entity.hpp>
#include <models/entities/damage_zone_entity.hpp>
#include <models/entities/item_entity.hpp>
#include <models/entities/krampus_entity.hpp>
#include <item_type_nums.hpp>



EntityFactory *EntityFactory::get_instance()
{
   if (!instance) instance = new EntityFactory();
   return instance;
}



EntityFactory::EntityFactory()
   : character_sprite_sheet(SPRITES_GRID_FILENAME, SPRITES_GRID_SPRITE_WIDTH, SPRITES_GRID_SPRITE_HEIGHT, SPRITES_GRID_SPRITE_SCALING)
   , flat_color_shader("data/shaders/flat_color_shader.vertex.glsl", "data/shaders/flat_color_shader.fragment.glsl")
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
{
   background1 = create_pixel_perfect_scaled_render(Framework::bitmap("background-1-08.png"), 5);
   background2 = create_pixel_perfect_scaled_render(Framework::bitmap("background-2-02.png"), 5);
   background3 = create_pixel_perfect_scaled_render(Framework::bitmap("background-3-02b.png"), 5);
   background4 = create_pixel_perfect_scaled_render(Framework::bitmap("background-4-01.png"), 5);
   background5 = create_pixel_perfect_scaled_render(Framework::bitmap("background-5-01.png"), 5);
   background6 = create_pixel_perfect_scaled_render(Framework::bitmap("background-6-02.png"), 5);
   door1 = create_pixel_perfect_scaled_render(Framework::bitmap("door-1-02.png"), 5);
   door2 = create_pixel_perfect_scaled_render(Framework::bitmap("door-2-01.png"), 5);
   door3 = create_pixel_perfect_scaled_render(Framework::bitmap("door-3-01.png"), 5);
   door4 = create_pixel_perfect_scaled_render(Framework::bitmap("door-4-01.png"), 5);
   door5 = create_pixel_perfect_scaled_render(Framework::bitmap("door-5-01.png"), 5);
   door6 = create_pixel_perfect_scaled_render(Framework::bitmap("door-6-01.png"), 5);
}



EntityBase *EntityFactory::create_random_kid(ElementID *parent, float x, float y)
{
   behavior_t behavior = (behavior_t)random_int(BEHAVIOR_ADULT, BEHAVIOR_NICE);
   return new KidEntity(parent, &get_instance()->character_sprite_sheet, &get_instance()->flat_color_shader, x, y, "[random name]", behavior, -1, -1);
}



KidEntity *EntityFactory::create_named_kid(ElementID *parent, std::string name, behavior_t behavior, int sprite_index, float x, float y)
{
   int identity_sprite_index = 29;
   if (behavior == BEHAVIOR_NAUGHTY) identity_sprite_index = 28;
   else if (behavior == BEHAVIOR_NICE) identity_sprite_index = 27;
   return new KidEntity(parent, &get_instance()->character_sprite_sheet, &get_instance()->flat_color_shader, x, y, name, behavior, sprite_index, identity_sprite_index);
}



KnightEntity *EntityFactory::create_knight_entity(ElementID *parent, float x, float y)
{
   return new KnightEntity(parent, &get_instance()->character_sprite_sheet, &get_instance()->flat_color_shader, x, y, "Harold", knight_behavior_t::BEHAVIOR_NORMAL, 32, -1);
}



EntityBase *EntityFactory::create_krampus(ElementID *parent, float x, float y)
{
   return new KrampusEntity(parent, &get_instance()->character_sprite_sheet, x, y);
}



EntityBase *EntityFactory::create_krampus_attack_damage_zone(ElementID *parent, float x, float y, float w, float h)
{
   return new DamageZoneEntity(parent, "krampus_damage_zone", false, true, x, y, w, h);
}



EntityBase *EntityFactory::create_krampus_attack_damage_zone_with_club(ElementID *parent, float x, float y, float w, float h)
{
   return new DamageZoneEntity(parent, "krampus_damage_zone_club", false, true, x, y, w, h);
}



EntityBase *EntityFactory::create_enemy_attack_damage_zone(ElementID *parent, float x, float y, float w, float h)
{
   return new DamageZoneEntity(parent, "enemy_attack_damage_zone", true, false, x, y, w, h);
}



EntityBase *EntityFactory::create_background1(ElementID *parent, float x, float y)
{
   return new BackgroundEntity(parent, get_instance()->background1, x, y);
}



EntityBase *EntityFactory::create_background2(ElementID *parent, float x, float y)
{
   return new BackgroundEntity(parent, get_instance()->background2, x, y);
}



EntityBase *EntityFactory::create_background3(ElementID *parent, float x, float y)
{
   return new BackgroundEntity(parent, get_instance()->background3, x, y);
}



EntityBase *EntityFactory::create_background4(ElementID *parent, float x, float y)
{
   return new BackgroundEntity(parent, get_instance()->background4, x, y);
}



EntityBase *EntityFactory::create_background5(ElementID *parent, float x, float y)
{
   return new BackgroundEntity(parent, get_instance()->background5, x, y);
}



EntityBase *EntityFactory::create_background6(ElementID *parent, float x, float y)
{
   return new BackgroundEntity(parent, get_instance()->background6, x, y);
}



EntityBase *EntityFactory::create_door1(ElementID *parent, float x, float y, std::string name, int destination_scene, std::string destination_door_name)
{
   return new DoorEntity(parent, name, destination_scene, destination_door_name, get_instance()->door1, x, y);
}



EntityBase *EntityFactory::create_door2(ElementID *parent, float x, float y, std::string name, int destination_scene, std::string destination_door_name)
{
   return new DoorEntity(parent, name, destination_scene, destination_door_name, get_instance()->door2, x, y);
}



EntityBase *EntityFactory::create_door3(ElementID *parent, float x, float y, std::string name, int destination_scene, std::string destination_door_name)
{
   return new DoorEntity(parent, name, destination_scene, destination_door_name, get_instance()->door3, x, y);
}



EntityBase *EntityFactory::create_door4(ElementID *parent, float x, float y, std::string name, int destination_scene, std::string destination_door_name)
{
   return new DoorEntity(parent, name, destination_scene, destination_door_name, get_instance()->door4, x, y);
}



EntityBase *EntityFactory::create_door5(ElementID *parent, float x, float y, std::string name, int destination_scene, std::string destination_door_name)
{
   return new DoorEntity(parent, name, destination_scene, destination_door_name, get_instance()->door5, x, y);
}



EntityBase *EntityFactory::create_door6(ElementID *parent, float x, float y, std::string name, int destination_scene, std::string destination_door_name)
{
   return new DoorEntity(parent, name, destination_scene, destination_door_name, get_instance()->door6, x, y);
}



EntityBase *EntityFactory::create_club_item(ElementID *parent, float x, float y)
{
   return new ItemEntity(parent, get_instance()->character_sprite_sheet.get_sprite(23), ITEM_TYPE_CLUB, x, y);
}



EntityBase *EntityFactory::create_stone_of_defiance_item(ElementID *parent, float x, float y)
{
   return new ItemEntity(parent, get_instance()->character_sprite_sheet.get_sprite(24), ITEM_TYPE_STONE_OF_DEFIANCE, x, y);
}



EntityBase *EntityFactory::create_naughty_list_item(ElementID *parent, float x, float y)
{
   return new ItemEntity(parent, get_instance()->character_sprite_sheet.get_sprite(25), ITEM_TYPE_NAUGHTY_LIST, x, y);
}



EntityBase *EntityFactory::create_key_item(ElementID *parent, float x, float y)
{
   return new ItemEntity(parent, get_instance()->character_sprite_sheet.get_sprite(26), ITEM_TYPE_KEY, x, y);
}



EntityBase *EntityFactory::create_hit_damage_motion_fx(ElementID *parent, float x, float y, std::string damage_string)
{
   return new MotionFXHitDamage(parent, x, y, damage_string);
}



EntityFactory *EntityFactory::instance = nullptr;



