#include "miniGit.hpp"
//#include "miniGit.cpp"

void menu(){
  cout<<"\na to ADD file"<<endl;
  cout<<"r to REMOVE file"<<endl;
  cout<<"c to COMMIT"<<endl;
  cout<<"h to CHECKOUT (You will loose your local changes if you checkout to a different version)"<<endl;
  cout<<"q to QUIT"<<endl;
  cout<<"Enter Choice: ";
}

int main(){
  DoublyLinkedList list;
  char choice;
  do{
    menu();
    cin>>choice;
    if(choice=='a'){
      list.add();
    }else if(choice=='r'){
      list.removeFile();
    }else if(choice=='c'){
      if(!list.isEmpty()){
        list.commitNum();
        list.deepCopy();
        cout<<"\n\nAfter Commit List"<<endl<<endl;
        list.display();
      }
    }else if(choice=='h'){
      list.checkOut();
    }else if(choice=='q'){
      cout<<"GOODBYE!"<<endl;
    }else{
      cout<<"INVALID CHOICE!"<<endl;
    }
  }while(choice!='q' && choice!='Q');
  return 0;
}