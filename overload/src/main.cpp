#include <iostream>

/// 在编译期间自动推导出变量的类型

using namespace std;

class CA{
public:
  CA(){}

  void fun_0(){
    cout<<"CA this "<<__func__<<endl;
  }

  void fun_1(){
    cout<<"CA this "<<__func__<<endl;
    fun_0();
  }
};

class CB :public CA{
public:
  CB(){}

  void fun_0(){
    cout<<"CB this "<<__func__<<endl;
  }

  //  void fun_1(){
  //    cout<<"CB this "<<__func__<<endl;
  //    fun_0();
  //  }
};





int main(int argc, char *argv[])
{
  CB cb;
  cb.fun_1();
  cb.fun_0();
  return 0;
}
