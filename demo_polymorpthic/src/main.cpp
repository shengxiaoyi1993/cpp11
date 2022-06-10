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



/// 静态成员函数的继承测试
///

class Parent{
public:
  virtual ~Parent()
  {

  }
  static Parent* getInstance();

  void func(int a) const{
    std::cout<<"const func"<<std::endl;
  }

  virtual void func(int a){
    std::cout<<"normal func"<<std::endl;
  }


};
Parent* Parent::getInstance()
{
  std::cout<<"static Parent::getInstance"<<std::endl;
  return nullptr;
}


class ChildA:public Parent
{
public:
  ~ChildA(){
    std::cout<<"~ChildA"<<std::endl;
  }

  static ChildA* getInstance()
  {
    std::cout<<"static ChildA::getInstance"<<std::endl;
    return nullptr;
  }
};

using namespace std;

class A
{
public:
    static void Print(void *pA, const char *str)
    {
        A *pa = reinterpret_cast<A*>(pA);
        pa->pPrint(str);
    }

    virtual void pPrint(const char *str)
    {
        cout << "A: " << str <<endl;
    }
};




class B : public A
{
public:
    virtual void pPrint(const char *str)
    {
        cout << "B: " << str <<endl;
    }
};


class AbstractBase{
public:
  AbstractBase() = default;
  virtual ~AbstractBase() = default;
  virtual void say() = 0;
};

class ConcreteA:public AbstractBase{
public:
  ~ConcreteA()
  {
    std::cout<<"~ConcreteA"<<std::endl;
  }

  void say()
  {
    std::cout<<"is ConcreteA"<<std::endl;
  }

};



int main(int argc, char *argv[])
{
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
  }

  {
    Parent p;
    p.func(1);
    /// 通过一个临时的const引用来调用到带有const的成员函数
    const Parent& b = p;
    b.func(2);
  }

  {
    ChildA childa;
    childa.getInstance();
    Parent* p=&childa;
    p->getInstance();
  }

  {
      A *a = new B;
      a->Print(a,"http://blog.csdn.net/lonelyrains");
      A::Print(a,"http://blog.csdn.net/lonelyrains");
  }

  ///测试抽象类能否作为被绑定对象
  {
    ConcreteA a;
    AbstractBase *ab=&a;
    ab->say();
  }


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
