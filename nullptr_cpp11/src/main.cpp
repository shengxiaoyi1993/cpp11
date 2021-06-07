#include <iostream>
///NULL 并不是 C++ 的关键字，它是 C++ 为我们事先定义好的一个宏，并且它的值往往就是字面量 0（#define NULL 0）
/// 因此，有时候使用时会导致0与NULL混淆的情况
/// c++11的nullptr是nullptr_t可以解决这个问题


using namespace std;
void isnull(void *c){
    cout << "void*c" << endl;
}
void isnull(int n){
    cout << "int n" << endl;
}

int main(int argc, char *argv[])
{
  std::cout<<"hello !"<<std::endl;
  isnull(0);
//  isnull(NULL);
//  isnull(NULL);
  isnull(nullptr);
  isnull((void*)0);

  return 0;
}
