//
// Created by masad on 7/17/2023.
//

#include <iostream>
using namespace std;

int getANumberFunction(){
  return 8;
}

void printANumberProcedure(){
  cout << 8 << endl;
}

class Kelas { // Pendeklarasian sebuah class
  
  private:
  int a = 8; // attribute
  int b; // attribute
  
  public:
  int c; // attribute
  
  Kelas(int b){ // Constructor
    this->b = b;
  }
  
  Kelas(){ // Constructor
  }
  
  
  // Contoh Beberapa Methods dalam C++ class
  
  int getA(){ // Function methods, karena memberikan nilai balikan
    return this->a;
  }
  
  int getB(){ // Function methods, karena memberikan nilai balikan
    return this->b;
  }
  
  void setA(int newA){ // Procedure methods, karena tidak memberikan nilai balikan
    this->a = newA;
  }
  
  void setB(int newB){ // Procedure methods, karena tidak memberikan nilai balikan
    this->b = newB;
  }
  
  void printAllAttributes(){ // Procedure methods, karena tidak memberikan nilai balikan
    cout << "A = " << getA() << endl;
    cout << "B = " << getB() << endl;
    if (this->c) cout << "C = " << this->c << endl;
    else cout << "The C attribute is not assigned with any value yet." << endl;
  }
  
};

int main() {
  
  cout << getANumberFunction() << endl;
  printANumberProcedure();
  
  cout << endl;
  
  
  cout << "====== Kelas 1 ======" << endl;
  
  Kelas kelas1;
  cout << "A = " << kelas1.getA() << endl;
  kelas1.setA(2);
  cout << "A = " << kelas1.getA() << endl;
  kelas1.setB(3);
  cout << "B = " << kelas1.getB() << endl;
  kelas1.c = 1;
  cout << "C = " << kelas1.c << endl;
  
  cout << endl;
  
  cout << "====== Kelas 2 ======" << endl;
  
  Kelas * kelas2 = new Kelas(4);
  kelas2->printAllAttributes();
  
  return 0;
}


