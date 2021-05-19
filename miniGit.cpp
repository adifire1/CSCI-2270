#include "miniGit.hpp"

DoublyLinkedList::DoublyLinkedList() {
  header = NULL;
  current = NULL;
}
bool DoublyLinkedList::isEmpty() {
  if (header == NULL) {
    return true;
  }
  return false;
}

void DoublyLinkedList::add() {
  string fileN;
  cout << "Enter file name: ";
  cin >> fileN;
  ifstream ifile(fileN);
  while (!ifile) {
    cout << "Enter valid File name: ";
    cin >> fileN;
    ifile.open(fileN);
  }

  if (isEmpty()) {
    doublyNode* tempp = new doublyNode;
    tempp->previous = NULL;
    tempp->next = NULL;
    tempp->cur = NULL;
    singlyNode* node = new singlyNode;
    node->fileName = fileN;
    fileN = fileNameV(fileN, 0);
    node->fileVersion = fileN;
    node->next = NULL;
    tempp->head = node;
    tempp->cur = node;
    tempp->commitNumber = 0;
    header = tempp;
    current = tempp;
  } else {
    bool check = true;
    singlyNode* temp = current->head;
    while (temp != NULL) {
      if (temp->fileName == fileN) {
        check = false;
      }
      temp = temp->next;
    }
    if (check) {
      singlyNode* node = new singlyNode;
      node->fileName = fileN;
      fileN = fileNameV(fileN, 0);
      node->fileVersion = fileN;
      node->next = NULL;
      current->cur->next = node;
      current->cur = node;
    }
  }
}

string DoublyLinkedList::fileNameV(string name, int ver) {
  string result = "";
  string ext = "";
  bool check = true;
  for (int i = 0; i < name.size(); i++) {
    if (name[i] == '.' || !check) {
      ext += name[i];
      check = false;
    }
    if (check) {
      result += name[i];
    }
  }
  result += "_" + to_string(ver);
  result += ext;
  return result;
}

void DoublyLinkedList::removeFile() {
  if (!isEmpty()) {
    singlyNode* temp = current->head;

    singlyNode* node;
    string fName;
    cout << "Enter file Name to remove file: ";
    cin >> fName;
    if (temp->fileName == fName) {
      if (current->head->next) {
        current->head = current->head->next;
      } else {
        current->head = NULL;
      }
      delete temp;
      return;
    } else if (current->cur->fileName == fName) {
      singlyNode* last = current->cur;
      while (last->next != NULL) {
        last = last->next;
      }
      singlyNode* temp2 = current->cur;
      temp->next = NULL;
      delete temp2;
      current->cur = last;
      return;
    }
    while (temp != NULL) {
      if (temp->fileName == fName) {
        singlyNode* del = temp;
        temp = temp->next;
        node->next = temp;
        delete del;
        break;
      }
      node = temp;
      temp = temp->next;
    }
  }
}
void DoublyLinkedList::commitNum() {
  singlyNode* temp = current->head;
  while (temp != NULL) {
    string ile = "";
    ile += ".minigit\\";
    ile += temp->fileVersion;
    ifstream ifile(ile);
    if (!ifile) {
      string fileData;
      ofstream ofile(ile);
      ifstream file(temp->fileName);
      getline(file, fileData);
      ofile << fileData;
      while (getline(file, fileData)) {
        ofile << "\n" << fileData;
      }
      ofile.close();
      ifile.open(ile);
    }
    string file1 = "", file2 = "", fil;
    ifstream file(temp->fileName);
    while (getline(file, fil)) {
      file1 += fil;
    }

    while (getline(ifile, fil)) {
      file2 += fil;
    }
    if (file1 != file2) {
      int j = 0;
      string fileN = "";
      fileN += ".minigit\\";
      string tem = fileNameV(temp->fileName, j);
      fileN += fileNameV(temp->fileName, j);
      ifstream ifile(fileN);
      while (ifile) {
        j++;
        fileN = "";
        fileN += ".minigit\\";
        fileN += fileNameV(fileN, j);
        tem = fileNameV(temp->fileName, j);
        ifile.open(fileN);
      }
      temp->fileVersion = tem;
      string name = "";
      name += ".minigit\\";
      name += tem;
      ofstream ofile(name);
      ifstream il(temp->fileName);
      getline(il, fileN);
      ofile << fileN;
      while (getline(il, fileN)) {
        ofile << "\n" << fileN;
      }
      ofile.close();
    }
    temp = temp->next;
  }
}
void DoublyLinkedList::checkOut() {
  doublyNode* temp = header;
  int commit;
  cout << "Enter Commit number: ";
  cin >> commit;
  if (commit < 0) {
    cout << "Invalid Commit number" << endl;
    return;
  }
  while (temp != NULL) {
    if (temp->commitNumber == commit) {
      overWrittenFile(temp->head);
    }
    temp = temp->next;
  }
}
void DoublyLinkedList::overWrittenFile(singlyNode* temp) {
  while (temp != NULL) {
    string file;
    string name = "";
    name += ".minigit\\";
    name += temp->fileVersion;
    ifstream ifile(name);
    ofstream ofile(temp->fileName);
    while (getline(ifile, file)) {
      ofile << file << endl;
    }
    temp = temp->next;
  }
}

void DoublyLinkedList::deepCopy() {
  singlyNode* node = current->head;
  doublyNode* tempp = new doublyNode;
  tempp->previous = NULL;
  tempp->next = NULL;
  tempp->cur = NULL;
  tempp->head = NULL;
  bool checkHead = false;
  while (node != NULL) {
    singlyNode* snode = new singlyNode;
    snode->fileName = node->fileName;
    snode->fileVersion = node->fileVersion;
    snode->next = NULL;
    if (!checkHead) {
      tempp->head = snode;
      tempp->cur = snode;
      checkHead = true;
    } else {
      tempp->cur->next = snode;
      tempp->cur = snode;
    }
    node = node->next;
  }
  tempp->commitNumber = current->commitNumber + 1;
  current->next = tempp;
  tempp->previous = current;
  current = tempp;
}

void DoublyLinkedList::display() {
  doublyNode* node = header;
  while (node != NULL) {
    cout << "Commit Number: " << node->commitNumber << "\n   List: ";
    singlyNode* temp = node->head;
    while (temp != NULL) {
      cout << temp->fileName << " " << temp->fileVersion << " ";
      temp = temp->next;
    }
    cout << endl << endl;
    node = node->next;
  }
}