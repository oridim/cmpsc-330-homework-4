Name: Ozge Selin Ak + Dimitri Orion Nearchos
Email: osa5177@psu.edu + don5092@psu.edu
Class: CMPSC 330
Section: 001

Assignment: Homework 4
Due Date: October 19th, 2024

Build Commands:

    * `...directory.../compile-dotsandboxes.sh`

Run Commands:

    * `...directory.../dotsandboxes  < "...directory.../testcase.txt"`

Acknowledgments:

    > See each individual source file for their individual acknowledgments, if any.

    1. Generally, we (Ozge and Dimitri) used C++ reference documentation provided by:
       https://cplusplus.com/reference

    2. Unless stated otherwise, we (Ozge and Dimitri) implemented everything in the
       source code from scratch.

Program Structures:

    1. `BasicStrategyAIPlayer`

        1.1. This class implements an AI player that uses basic heuristics to decide moves in the game.
             It analyzes the game board and selects moves based on predefined strategies.

        1.2. Calculate the number of surrounding lines around a specific slot.
             Determine the AI's next move using the `computePlayerMove` method.

    2. `DummyPlayer`

        2.1. Represents a placeholder player used primarily for testing purposes or to fill player slots in a game.
             It doesn't employ complex strategies and may implement minimal or random move logic.

        2.2. Overrides the computePlayerMove method to decide moves for testing or simulation.
             Provides a simple implementation of a player without strategic behavior.
   
    3. `GameBoardSlot`

        3.1. Represents an individual slot on the game board where a line can be drawn.
 
        3.2. Maintains the state of a specific slot.

    4. `GameBoard`

        4.1. Represents the game's playing field, consisting of slots where lines can be drawn.

        4.2. Store the state of the board.
             Provides methods to query or manipulate the board state.

    5. `GameConfiguration`

        5.1. Manages the setup of the Dots and Boxes game.
             This including defining player types and initializing the game board and session based on the configuration.

        5.2. Stores and manages the configuration data for a Dots and Boxes game.
             Provides methods to deserialize a game configuration, create players based on the configuration, initialize session.
             Defines player types through an enumeration and provides helper methods to generate the corresponding player objects.

    6. `GameData`

        6.1. Stores and manages the recorded data of a Dots and Boxes game
             This including the game grid dimensions and the sequence of player turns.
 
        6.2. Store game grid dimensions (rows and columns).
             Manage a collection of player turn data (`PlayerTurn`).
             Provide functionality to deserialize game data from an input stream and reconstruct the game board.
   
    7. `GameResult`

        7.1. Represents and manages the results of a completed Dots and Boxes game, including the winners, the highest score, and the overall game outcome.

        7.2. Store and track the highest score and win state of the game.
             Store results for each player, including their score and win state.
             Provide functionality to compute the game result based on the session and board data, and serialize the results.

    8. `GameSession`

        8.1. Represents an ongoing session of the Dots and Boxes game, managing the players, turn order, and game flow.

        8.2. Maintain a list of players and their respective turns.
             Determine and prompt the next player to make a move.
             Provide mechanisms to compute and apply valid moves.
             Manage the history of turns.

    9. `PlayerMove`

        9.1. Encapsulates a player's move details, such as the action performed during a turn.

        9.2. Represent the move in a structured format.
             Include information for validation or processing the move.

    10. `PlayerResult`

        10.1. Represents the result data for a player in a Dots and Boxes game, including their score and win state.

        10.2. Stores and manages a player's initial, score, and win state in a game.
              Provides methods for comparing player results for equality or inequality.
              Encapsulates player data, making it accessible through getter methods while protecting internal details.

    11. `PlayerTurn`

        11.1. Represents a single turn in the game, encapsulating the action taken by a player during that turn.

        11.2. Record details of a player's move.
              Provide functionality for querying and applying the turn's effects on the game state.

    12. `Player`

        12.1. Serves as the base class for all player types in the game. 
              It provides shared functionality and attributes for both human and AI players.

        12.2. Define common behaviors for players.
              Acts as a polymorphic base for specialized player classes.

    13. `RandomAIPlayer`

        13.1. Represents an AI player that makes completely random moves during its turn, selecting from the list of available moves.

        13.2. Override the 'computePlayerMove' method to randomly choose a move from the valid options.
              Serve as a simple AI implementation with no strategic logic.
    
    14. `SimpleHashMap`

        14.1. Implements a simple hash table that maps keys (K) to values (V) using an array of hash nodes. 
              The hash table supports basic operations like insertion, retrieval, and removal of key-value pairs.

        14.2. Stores key-value pairs in a hash table and ensures efficient lookups using hashing and collision resolution.
              Provides methods to insert, retrieve, and remove key-value pairs while managing memory allocation and deallocation.
              Allows access to all keys and values, and supports comparison of hash map instances for equality or inequality.

    15. `SimpleHashNode`

        15.1. Represents a single node in a hash table, storing a key-value pair.

        15.2. Hold a key (K) and a corresponding value (V).
              Provide access to the key and value through getter methods.
              Support copy construction to create new instances from existing nodes.

    16. `SimpleVector`

        16.1. A utility class that acts as a dynamic array, used to store collections

        16.2. Manage a resizable collection of elements.
              Allow efficient access and iteration over stored objects.

Program Flowchart:

+---------------------------+
| Program Enter (main.cxx)  |
+---------------------------+
             |
             v
+--------------------------------------+
| GameConfiguration                    |
| (Deserialize from input via cin)     |
+--------------------------------------+
             |
             v
  +---------------------+    +--------------------+
  | Create GameBoard    | <--| GameConfiguration  |
  +---------------------+    +--------------------+
             |
             v
  +---------------------+    +--------------------+
  | Create GameSession  | <--| GameConfiguration  |
  +---------------------+    +--------------------+
             |
             v
  +------------------------------------+
  | Seed RNG (time)                    |
  +------------------------------------+
             |
             v
  +------------------------------------+
  | Game Loop                          |
  | (while captures remain)            |
  +------------------------------------+
             |
             v
  +-----------------------+     +-------------------------+
  | Check available       |---> | If no captures: break   |---+
  | captures in GameBoard |     +-------------------------+   |
  +-----------------------+                                   |
             |      ⌃----------------------------------+      |
             v                                         |      |
  +------------------------------------------------+   |      |
  | Select Next Player from GameSession turn order |   |      |
  +------------------------------------------------+   |      |
             |                                         |      |
             v                                         |      |
  +-------------------------------------------+        |      |
  | Player computes a turn, if possible:      |        |      |
  | - Determines best move                    |        |      |
  | - Updates the GameBoard with new captures |        |      |
  +-------------------------------------------+        |      |
             |                                         |      |
             v                                         |      |
  +-------------------------------------------+        |      |
  | Update Player Queue:                      |        |      |
  | - If captures: Player takes another turn  |--------+      |
  | - If no captures: Player moved to back    |               |
  +-------------------------------------------+               |
                                                              |
                                                              |
  +-----------------------------+                             |
  | Serialize GameBoard state   | <---------------------------+
  +-----------------------------+
             |
             |
             |
             v
  +----------------------------------------------+
  | Write serialized GameBoard state to terminal |
  | (intermediate state output)                  |
  +----------------------------------------------+
             |
             |
             v
  +------------------------------------+
  | End of Loop                        |
  +------------------------------------+
             |
             v
  +--------------------------------------+
  | Compute GameResult using             |
  | GameSession and GameBoard            |
  +--------------------------------------+
             |
             v
  +--------------------------------------+
  | Serialize Final States:              |
  | - GameData                           |
  | - Final GameBoard state              |
  | - GameResult                         |
  +--------------------------------------+
             |
             |
             |
             v
  +-------------------------+
  | Write serialized data   |
  | to terminal (output)    |
  +-------------------------+
             |
             v
  +--------------------------------------+
  | Clean up dynamically allocated       |
  | objects (delete pointers)            |
  +--------------------------------------+
             |
             v
  +---------------------------+
  |        Program Exit       |
  +---------------------------+