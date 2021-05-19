#ifndef MINIGIT_HPP
#define MINIGIT_HPP

#include <iostream>
#include <fstream>
using namespace std;

struct singlyNode {
  string fileName;     // Name of local file
  string fileVersion;  // Name of file in .minigit folder
  singlyNode* next;
};

struct doublyNode {
  int commitNumber;
  singlyNode* head;
  singlyNode* cur;
  doublyNode* previous;
  doublyNode* next;
};

class DoublyLinkedList {
 private:
  doublyNode* header;
  doublyNode* current;

 public:
  DoublyLinkedList();
  bool isEmpty();
  void add();
  string fileNameV(string name, int ver);
  void removeFile();
  void commitNum();
  void checkOut();
  void overWrittenFile(singlyNode* temp);
  void deepCopy();
  void display();
};
#endif