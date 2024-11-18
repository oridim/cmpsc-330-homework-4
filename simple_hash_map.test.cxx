#include <iostream>

#include "simple_vector.h"
#include "simple_hash_map.h"

#include "player_result.cxx"

using namespace std;

int main()
{
    cout << "=> [UNIT TEST: simple_hash_map.test.cxx]" << endl
         << endl;

    // **NOTE**: A `SimpleHashMap` internally contains a 2D array data structure. So,
    // when the hashmap is initialized with the below 256 it will create a internal
    // dynamic array with a capacity of 256 slots.

    SimpleHashMap<char, char, 256> hashMap1;

    // Test the at() and get() methods by assigning values to keys and verifying retrieval.
    cout
        << "SimpleHashMap::at, SimpleHashMap::get" << endl
        << endl
        << "hashMap1.at(0)\t\t= 'p'" << endl
        << "hashMap1.at('s')\t= 'u'" << endl
        << "hashMap1.at(\"hello\")\t= 'w'" << endl
        << endl;

    // Assign values to keys using at() method.
    hashMap1.at(0) = 'p';
    hashMap1.at('s') = 'u';

    // Display assigned values and check if they match.
    cout
        << "\thashMap1.at(0):\t\t" << "'" << hashMap1.at(0) << "'" << "\t(SHOULD BE: 'p')" << endl
        << "\thashMap1.get('s'):\t" << "'" << hashMap1.get('s') << "'" << "\t(SHOULD BE: 'u')" << endl;

    // Test the remove method by removing the key 's'.
    cout << endl
         << "SimpleMap::remove" << endl
         << endl
         << "hashMap1.remove('s')" << endl;

    hashMap1.remove('s');

    // Test has() method to check if certain keys are still present
    cout
        << endl
        << "SimpleHashMap::has" << endl
        << endl;

    // Retrieve all keys in hashMap1 using the keys() method and store in assignedKeys.
    cout
        << "\thashMap1.has(0):\t" << (hashMap1.has(0) ? "true" : "false") << "\t(SHOULD BE: true)" << endl
        << "\thashMap1.has('s'):\t" << (hashMap1.has('s') ? "true" : "false") << "\t(SHOULD BE: false)" << endl;

    SimpleVector<char> *assignedKeys = hashMap1.keys();

    // Expected values output and Actual values ouput
    cout << endl
         << "assignedKeys = hashMap1.keys()" << endl
         << endl
         << "(SHOULD BE)" << endl
         << endl
         << "assignedKeys->at(0):\t0" << endl
         << "assignedKeys->at(1):\t20" << endl
         << endl
         << "(ACTUAL)" << endl
         << endl;

    // Iterate over each assigned key in the hash map and print it
    for (int index = 0; index < assignedKeys->size(); index++)
    {
        int key = assignedKeys->at(index);

        cout << "\tassignedKeys->at(" << index << "):\t" << key << endl;
    }

    // Retrieve the values from the hash map and store them in assignedValues
    SimpleVector<char> *assignedValues = hashMap1.values();

    // Output information about the retrieved values
    cout << endl
         << "assignedValues = hashMap1.values()" << endl
         << endl
         << "(SHOULD BE)" << endl
         << endl
         << "assignedValues->at(0):\t'p'" << endl
         << "assignedValues->at(1):\t'w'" << endl
         << endl
         << "(ACTUAL)" << endl
         << endl;

    // Iterate over each assigned value in the assignedValues vector and print it
    for (int index = 0; index < assignedValues->size(); index++)
    {
        char value = assignedValues->at(index);

        cout << "\tassignedValues->at(" << index << "):\t'" << value << "'" << endl;
    }

    SimpleHashMap<char, PlayerResult, 128> hashMap2;

    // Add an entry for the player with initial 'D' and a score of 117, marking it as a winner
    cout
        << endl
        << "hashMap2.at('D')\t= PlayerResult('D', 117, PlayerResult::WIN_KIND::singular)" << endl;

    // Assign a PlayerResult object to the hash map for player 'D'
    hashMap2.at('D') = PlayerResult('D', 117, PlayerResult::WIN_KIND::winner);
    PlayerResult &playerResult = hashMap2.at('D');

    // Output the player result for 'D' and validate its attributes
    cout
        << endl
        << "playerResult = hashMap2.at('D'): " << endl
        << endl
        << "\tplayerResult.playerInitial()\t= '" << playerResult.playerInitial() << "'\t(SHOULD BE: 'D')" << endl
        << "\tplayerResult.score()\t\t= " << playerResult.score() << "\t(SHOULD BE: 117)" << endl
        << "\tplayerResult.winKind()\t\t= " << static_cast<int>(playerResult.winKind()) << "\t(SHOULD BE: 2)\t[PlayerResult::WIN_KIND::winner]" << endl;

    // Clean up dynamically allocated memory
    delete assignedKeys;
    delete assignedValues;

    return 0;
}