


#include <gtest/gtest.h>

#include <models/inventory.hpp>



TEST(InventoryTest, can_be_created)
{
   Inventory inventory;
}



TEST(InventoryTest, get_ordered_item__returns_the_expected_sorted_item)
{
   Inventory inventory;

   inventory.add_item(3);
   inventory.add_item(5);
   inventory.add_item(2);
   inventory.add_item(2);

   ASSERT_EQ(2, inventory.get_ordered_item(0));
   ASSERT_EQ(3, inventory.get_ordered_item(1));
   ASSERT_EQ(5, inventory.get_ordered_item(2));

   ASSERT_EQ(0, inventory.get_ordered_item(3));
   ASSERT_EQ(0, inventory.get_ordered_item(999));
   ASSERT_EQ(0, inventory.get_ordered_item(-1));
}


int main(int argc, char **argv)
{
   ::testing::InitGoogleTest(&argc, argv);
   return RUN_ALL_TESTS();
}


