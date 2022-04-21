#include <iostream>

/// 在编译期间自动推导出变量的类型


class Base{
public:
  virtual ~Base()
  {
    std::cout<<"~Base"<<std::endl;
  }
  virtual void say(){
    std::cout<<"I'm Base"<<std::endl;
  }
};

class SuperA:public Base
{
public:
  ~SuperA();
  void say();
};

class SuperB:public Base
{
public:
  ~SuperB();
  void say();
};




int main(int argc, char *argv[])
{
  SuperA *pa=new SuperA();
  SuperB *pb=new SuperB();
  pa->say();
  pb->say();

  Base *zpa=pa;
  Base *zpb=pb;
  zpa->say();
  zpb->say();

//  delete zpa;
//  delete zpb;
  delete pa;
  delete pb;




  return 0;
}

void SuperA::say()
{
  std::cout<<"I'm SuperA"<<std::endl;
}

SuperA::~SuperA()
{
  std::cout<<"~SuperA"<<std::endl;
}

void SuperB::say()
{
  std::cout<<"I'm SuperB"<<std::endl;
}

SuperB::~SuperB()
{
  std::cout<<"~SuperB"<<std::endl;
}
