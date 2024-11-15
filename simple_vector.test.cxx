#include <iostream>

#include "simple_vector.h"

using namespace std;

int main()
{
     cout << "=> [UNIT TEST: simple_vector.test.cxx]" << endl
          << endl;
     
     // Create a SimpleVector instance to hold integers
     SimpleVector<int> integers;

     // Push back 5 elements into the vector
     integers.push_back(42);
     integers.push_back(5);
     integers.push_back(24);
     integers.push_back(69);
     integers.push_back(255);

     // Display the size and capacity after pushing elements
     cout << "PUSHED 5 ELEMENTS, NEW SIZE " << integers.size() << ", NEW CAPACITY " << integers.capacity() << "\t(SHOULD BE: 5, 8)" << endl
          << endl;

     // List all elements in the vector
     cout << "LIST ELEMENTS:" << "\t\t\t\t\t(SHOULD BE: 42, 5, 24, 69, 255)" << endl;
     for (int index = 0; index < integers.size(); index++)
     {
          cout << integers.at(index) << endl;
     }

     cout << endl;

     // Find an element (69) and display its index and value
     int foundIndex = integers.find(69);
     int foundElement = integers.at(foundIndex);

     cout << "FOUND ELEMENT, " << foundElement << ", AT INDEX " << foundIndex << "\t\t\t(SHOULD BE: 69, 3)" << endl
          << endl;

     // Remove the found element and dispaly the new size of the vector
     integers.remove(foundIndex);
     cout << "REMOVED INDEX " << foundIndex << ", NEW SIZE " << integers.size() << "\t\t\t(SHOULD BE: 4)" << endl
          << endl;

     // Find an element (24) using a predicate function and display its index and value
     int predicateIndex = integers.find([](const int &element)
                              {
                                   return element == 24; 
                              });

     int predicateElement = integers.at(predicateIndex);

     // List all elements in the vector after removal
     cout << "FOUND ELEMENT (W/ PREDICATE), " << predicateElement << ", AT INDEX " << predicateIndex << "\t(SHOULD BE: 24, 2)" << endl
          << endl;

     cout << "LIST ELEMENTS:" << "\t\t\t\t\t(SHOULD BE: 42, 5, 24, 255)" << endl;
     for (int index = 0; index < integers.size(); index++)
     {
          cout << integers.at(index) << endl;
     }

     cout << endl;

     // Shrink vector capcity to fit its current size
     integers.shrink_to_fit();
     cout << "SHRUNK SimpleVector TO CAPACITY " << integers.capacity() << "\t\t(SHOULD BE: 4)" << endl;

     // Test equality operators between two empty SimpleVector instances
     SimpleVector<int> simpleVector1;
     SimpleVector<int> simpleVector2;

     cout << endl
          << "SimpleVector::operator==, SimpleVector::operator!=" << endl
          << endl
          << "\tsimpleVector1 == simpleVector1:\t" << ((simpleVector1 == simpleVector1) ? "true" : "false") << "\t(SHOULD BE: true)" << endl
          << "\tsimpleVector1 != simpleVector1:\t" << ((simpleVector1 != simpleVector1) ? "true" : "false") << "\t(SHOULD BE: false)" << endl
          << "\tsimpleVector1 == simpleVector2:\t" << ((simpleVector1 == simpleVector2) ? "true" : "false") << "\t(SHOULD BE: false)" << endl
          << "\tsimpleVector1 != simpleVector2:\t" << ((simpleVector1 != simpleVector2) ? "true" : "false") << "\t(SHOULD BE: true)" << endl
          << endl;

     // Copy the elements of the original 'integers' vector into a new vector, integersCopy
     cout << "integersCopy LIST ELEMENTS:" << "\t(SHOULD BE: 42, 5, 24, 255)" << endl;

     SimpleVector<int> integersCopy(integers);

     for (int index = 0; index < integersCopy.size(); index++)
     {
          cout << integersCopy.at(index) << endl;
     }

     // Sort integersCopy in ascending order using lambda function comparator
     cout
          << endl
          << "SORT SimpleVector BY NUMBER SIZE"
          << endl
          << endl
          << "integersCopy LIST ELEMENTS:" << "\t(SHOULD BE: 5, 24, 42, 255)" << endl;

     integersCopy.sort([](const int &a, const int &b)
          {
               if (a > b) {
                    return 1;
               }

               return 0;
          });
     
     // List all elements in integersCopy after sorting for verification.
     for (int index = 0; index < integersCopy.size(); index++)
     {
          cout << integersCopy.at(index) << endl;
     }

     return 0;
}