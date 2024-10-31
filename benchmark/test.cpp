#define CATCH_CONFIG_MAIN
#include <catch2/catch_all.hpp>

#include <cstdint>
#include <string>
#include "../headers/keydir.hpp"

using namespace std;

TEST_CASE("Benchmark the database's operations") {
    KeyDir keydir;

    BENCHMARK("Set Command Benchmark") {
        for (int i = 0; i < 20; i++) {
            keydir.set_command(to_string(i), to_string(i));
        }
    };

    BENCHMARK("Get Command Benchmark") {
        for (int i = 0; i < 20; i++) {
            keydir.get_command(to_string(i));
        }
    };
}
