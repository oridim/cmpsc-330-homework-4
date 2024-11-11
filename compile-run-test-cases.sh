#!/usr/bin/env bash

# **NOTE**: The below flag causes the Bash script to exit whenever a command fails.

set -e

# Rubric Test Cases

./dotsandboxes ./Rubric/game1.txt > ./Rubric/game1.stdout.txt
./dotsandboxes ./Rubric/game2.txt > ./Rubric/game2.stdout.txt
./dotsandboxes ./Rubric/game3.txt > ./Rubric/game2.stdout.txt
./dotsandboxes ./Rubric/game4.txt > ./Rubric/game4.stdout.txt
./dotsandboxes ./Rubric/game5.txt > ./Rubric/game5.stdout.txt
./dotsandboxes ./Rubric/game6.txt > ./Rubric/game6.stdout.txt
./dotsandboxes ./Rubric/game7.txt > ./Rubric/game7.stdout.txt
./dotsandboxes ./Rubric/game8.txt > ./Rubric/game8.stdout.txt
./dotsandboxes ./Rubric/game9.txt > ./Rubric/game9.stdout.txt
./dotsandboxes ./Rubric/game10.txt > ./Rubric/game10.stdout.txt
./dotsandboxes ./Rubric/game11.txt > ./Rubric/game11.stdout.txt
./dotsandboxes ./Rubric/game12.txt > ./Rubric/game12.stdout.txt
./dotsandboxes ./Rubric/game13.txt > ./Rubric/game13.stdout.txt
./dotsandboxes ./Rubric/game14.txt > ./Rubric/game14.stdout.txt

# Assignment Test Case

./dotsandboxes "./Test Cases/game.professor-supplied.txt" > "./Test Cases/game.professor-supplied.stdout.txt"

# Grid Size Test Cases

./dotsandboxes "./Test Cases/game.empty-grid.txt" > "./Test Cases/game.empty-grid.stdout.txt"

./dotsandboxes "./Test Cases/game.5x3-grid.txt" > "./Test Cases/game.5x3-grid.stdout.txt"
./dotsandboxes "./Test Cases/game.8x8-grid.txt" > "./Test Cases/game.8x8-grid.stdout.txt"

# Board State Test Cases

./dotsandboxes "./Test Cases/game.no-moves.txt" > "./Test Cases/game.no-moves.stdout.txt"

# Illegal Move Test Cases

./dotsandboxes "./Test Cases/game.bad-move.txt" > "./Test Cases/game.bad-move.stdout.txt"
# **NOTE:** We were not expected to error handle malformed data, so we should be capturing a segmentation fault below. 
{ ./dotsandboxes "./Test Cases/game.out-of-bounds.txt"; } 2> "./Test Cases/game.out-of-bounds.stderr.txt"

# Player Count Test Cases

./dotsandboxes "./Test Cases/game.three-players.txt" > "./Test Cases/game.three-players.stdout.txt"

# Winning Test Cases

./dotsandboxes "./Test Cases/game.single-winner.txt" > "./Test Cases/game.single-winner.stdout.txt"

# Tie Test Cases

./dotsandboxes "./Test Cases/game.two-winners.txt" > "./Test Cases/game.two-winners.stdout.txt"
./dotsandboxes "./Test Cases/game.two-winners.txt" > "./Test Cases/game.three-winners.stdout.txt"