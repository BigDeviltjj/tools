#include "memory.h"
#include <vector>
#include <memory>
#include <chrono>
#include <iostream>
#include "utils.h"
// #include <cxxabi.h>
using namespace std;

// automatic align memory, sizeof(Foo) must be factor of 64
// class alignas(64)
class Foo {
public:
  Foo() {
     cout<<"I am default constructor of "<<(typeid(*this).name())<<endl;
  }
  ~Foo() {
     cout<<"I am deconstructor of "<< (typeid(*this).name())<<endl;
  }
  void alive() const {
     cout<<"I am alive!"<<endl;
  }
  Foo(short Bar) : Foo_2(Bar) {
     cout<<"I am a constructor"<<endl;
  } 
  int Foo_1[16];
  short Foo_2;
};
void callALLOCA(Foo *f) {
    f = ALLOCA(Foo, 2); 
    cout<<"size of Foo: "<<sizeof(Foo)<<endl;
    cout<<"calling construct function"<<endl;
    new(f) Foo();
    new(f+1) Foo();
    // remember to call destructor, memory will be recyceled automatically
    // you don't have to call free() since memory will be freed automatically.
    f->~Foo();
    (f+1)->~Foo();
}
void useArena(int repeat) {
    Foo *f;
    MemoryArena arena;
    for (int i = 0;i < repeat ; ++i) {
      Foo *f = ARENA_ALLOC(arena, Foo)(32);
    }
}
void useNew(int repeat) {
    vector<Foo*> vFoo;
    for (int i = 0; i < repeat; ++i) {
      vFoo.push_back(new Foo(32));
    }
    for_each(vFoo.begin(), vFoo.end(), [](Foo *&f) { delete f;});
}
void compareArenaNew() {
    uint32_t repeat;
    cin>>repeat;
    testTime(bind(useArena, repeat), "useArena");
    testTime(bind(useNew, repeat), "useNew");
}
int main() {
    // usage1: ALLOCA(Type, Num), only allocate memory, do not call construction function
    Foo *f;
    callALLOCA(f);
    f->alive();
    (f+1)->alive();

    // usage2: compare with MemoryArena and new, results show that MemoryArena is 4 times faster than new
    compareArenaNew();
    

}
