#!/usr/bin/env bash

# **NOTE**: The below flag causes the Bash script to exit whenever a command fails.

set -e

# Compile Dots and Boxes Entry Point

g++ -ansi -pedantic -std=c++14 -Wall -g \
    "./basic_strategy_ai_player.cxx" \
    "./game_configuration.cxx" \
    "./game_board.cxx" \
    "./game_board_slot.cxx" \
    "./game_data.cxx" \
    "./game_result.cxx" \
    "./game_session.cxx" \
    "./player_move.cxx" \
    "./player_result.cxx" \
    "./player_turn.cxx" \
    "./random_ai_player.cxx" \
    "./main.cxx" -o "./dotsandboxes"
