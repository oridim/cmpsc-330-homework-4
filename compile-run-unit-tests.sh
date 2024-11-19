#!/usr/bin/env bash

# **NOTE**: The below flag causes the Bash script to exit whenever a command fails.

set -e

# **NOTE**: Compiles and test runs are done in least dependencies -> most dependencies.

# Compile Unit Tests

g++ -ansi -pedantic -std=c++14 -Wall -g './simple_vector.test.cxx' -o './simple_vector.test'
g++ -ansi -pedantic -std=c++14 -Wall -g './simple_hash_map.test.cxx' -o './simple_hash_map.test'

g++ -ansi -pedantic -std=c++14 -Wall -g './player_result.test.cxx' -o './player_result.test'
g++ -ansi -pedantic -std=c++14 -Wall -g './player_turn.test.cxx' -o './player_turn.test'

g++ -ansi -pedantic -std=c++14 -Wall -g './game_board_slot.test.cxx' -o './game_board_slot.test'
g++ -ansi -pedantic -std=c++14 -Wall -g './game_board.test.cxx' -o './game_board.test'


g++ -ansi -pedantic -std=c++14 -Wall -g './game_configuration.test.cxx' -o './game_configuration.test'
g++ -ansi -pedantic -std=c++14 -Wall -g './game_data.test.cxx' -o './game_data.test'
g++ -ansi -pedantic -std=c++14 -Wall -g './game_session.test.cxx' -o './game_session.test'
g++ -ansi -pedantic -std=c++14 -Wall -g './game_result.test.cxx' -o './game_result.test'

g++ -ansi -pedantic -std=c++14 -Wall -g './basic_strategy_ai_player.test.cxx' -o './basic_strategy_ai_player.test'
g++ -ansi -pedantic -std=c++14 -Wall -g './random_ai_player.test.cxx' -o './random_ai_player.test'

# Run Unit Tests

./simple_vector.test
./simple_hash_map.test

./player_result.test
./player_turn.test

./game_board_slot.test
./game_board.test

./game_configuration.test
./game_data.test
./game_session.test
./game_result.test

./basic_strategy_ai_player.test
./random_ai_player.test