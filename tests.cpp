#define CATCH_CONFIG_MAIN

#include "catch.hpp"

#include <string>
#include "include/DataModel.h"
#include "include/DataModelEntry.h"

typedef enum {
    ENTRY_NON = 0,
    ENTRY_A = 1,
    ENTRY_B,
    ENTRY_C,
    ENTRY_D,
} model_entry_types_t;


TEST_CASE("Initializing testing int type storage")
{
    DataModel<model_entry_types_t, int, std::string> obj;
    obj.set_entry(ENTRY_A, 123);
    obj.set_entry(ENTRY_B, 456);
    using namespace std::string_literals;
    obj.set_entry(ENTRY_C, "entry c"s);
    SECTION("Testing all has been set correctly")
    {
        REQUIRE(*obj.get_entry_object<int>(ENTRY_A) == 123);
        obj.set_entry(ENTRY_A, 321);
        REQUIRE(*obj.get_entry_object<int>(ENTRY_A) != 123);
        REQUIRE(*obj.get_entry_object<int>(ENTRY_A) == 321);
        REQUIRE(*obj.get_entry_object<int>(ENTRY_B) == 456);
        REQUIRE(*obj.get_entry_object<std::string>(ENTRY_C) == "entry c");
    }
    SECTION("Testing fetching of wrong types")
    {
        // When the wrong type is requested a nullptr is given back
        REQUIRE(obj.get_entry_object<int>(ENTRY_C) == nullptr);
        REQUIRE(obj.get_entry_object<std::string>(ENTRY_B) == nullptr);
    }
    SECTION("Testing equality operator for data entries.")
    {
        obj.set_entry(ENTRY_B, 123);
        REQUIRE((*obj.get_entry(ENTRY_A)) == (*obj.get_entry(ENTRY_B)));
        obj.set_entry(ENTRY_B, 999);
        REQUIRE((*obj.get_entry(ENTRY_A)) != (*obj.get_entry(ENTRY_B)));
    }
    SECTION("Testing has_changed parameter of entries.")
    {
        // When function is called the default parameter resets the flag.
        REQUIRE(obj.get_entry(ENTRY_A)->value_has_changed());
        REQUIRE(!obj.get_entry(ENTRY_A)->value_has_changed());
        // Setting new causes flag to trigger
        obj.set_entry(ENTRY_A, 999);
        REQUIRE(obj.get_entry(ENTRY_A)->value_has_changed());
        // Setting new value where == matches dose not set flag when bool is not set
        obj.set_entry(ENTRY_A, 999);
        REQUIRE(!obj.get_entry(ENTRY_A)->value_has_changed());
        // Setting new value where == matches dose not set flag when bool is not set
        obj.set_entry(ENTRY_A, 999, true);
        REQUIRE(obj.get_entry(ENTRY_A)->value_has_changed());
    }
}


