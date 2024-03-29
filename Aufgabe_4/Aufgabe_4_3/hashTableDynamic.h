
#ifndef Aufgabe_4_2_HASHTABBLEDYNAMIC_H
#define Aufgabe_4_2_HASHTABBLEDYNAMIC_H

#include <string>
#include "pbEntry.h"

typedef int (*hashFunctionPtr)(std::string);    //  typedefinition of a pointer for a hashfunction; they all need conform to the guideline: int <functionName>(std::string <param>) 
int lastNumber(std::string telNr);              //  hash algorithm that uses only the last digit of a given telNr
int firstThreeNumbers(std::string telNr);       //  hash algorithm that uses the first three digits of a given telNr
int lastThreeNumbers(std::string telNr);        //  hash algorithm that uses the last three digits of a given telNr
int mod17(std::string telNr);                   //  hash algorithm that takes a given telNr mod17
int mod37(std::string telNr);
int mod71(std::string telNr);

class HashTable {
    private:
        class HashFunction {                    //  private inner class to make hash functions managable
            public:
                int size;
                std::string name;
                hashFunctionPtr algorithm;
                
                HashFunction(std::string name, hashFunctionPtr algorithm, int size);    //  constructor
        };

        HashFunction availableAlgorithms[3] = { {"mod17", mod17, 17},
                                                {"mod37", mod37, 37},
                                                {"mod71", mod71, 71}};
        
        class HashNode {                    //  private inner class for HashNodes that have a key (which will be the telephone number) and a value of type PbEntry
            public:                         
                std::string key = "";
                PbEntry* phonebookEntry;
        };

    public:
        int size;                       //  m in lecture
        int numberOfEntries = 1;            //  n in lecture
        HashNode* entries;              //  nodes of the hash table
        hashFunctionPtr hashFunction;   //  pointer to the hash algorithm used is stored in a private variable of type hashFunctionPtr - see beginning of this file


        void insert(PbEntry* entry);
        const PbEntry* search(std::string key);
        bool deleteItem(std::string key);
        void print();
        void setHashFunction(std::string name);

        HashTable();                        //  default constructor
};

#endif