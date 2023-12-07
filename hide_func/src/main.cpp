#include <iostream>

/// 在编译期间自动推导出变量的类型



class A{
public:
  A(){
    std::cout<<__func__<<std::endl;
  }
  ~A(){
    std::cout<<__func__<<std::endl;
  }

  void doA(){
    std::cout<<__func__<<std::endl;
  }

  void doAA(){
    std::cout<<__func__<<std::endl;
  }
};

class B:public A{

public:
  B()
  {
    std::cout<<__func__<<std::endl;
  }

  ~B(){
    std::cout<<__func__<<std::endl;
  }

  void doB(){
    std::cout<<__func__<<std::endl;
  }

  void doA() = delete;

  void doAA();


};


int main(int argc, char *argv[])
{
  A a;
  a.doA();

  B b;
//  b.doA();
  b.doAA();





  return 0;
}
