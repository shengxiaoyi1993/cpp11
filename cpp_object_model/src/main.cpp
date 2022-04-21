#include <iostream>
//#include "export.h"


/// 构造函数、析构函数、虚函数、继承（单继承、多继承、虚继承）、多态
/// C++类中有两种成员数据：static、nonstatic；
/// 三种成员函数：static、nonstatic、virtual
/// 2种对象模型：简单对象模型（a simple object model）、表格驱动对象模型（a table-driven object model）
///
/// - 简单对象模型:对象只是维护了一个包含成员指针的一个表
///
/// - 表格驱动对象模型:
/// 在简单对象的基础上又添加了一个间接层。将成员分成函数和数据，并且用两个表格保存，然后对象只保存了两个指向表格的指针。
/// 这个模型可以保证所有的对象具有相同的大小，比如简单对象模型还与成员的个数相关。其中数据成员表中包含实际数据；
/// 函数成员表中包含的实际函数的地址（与数据成员相比，多一次寻址）。
///
/// - C++对象模型
/// 这个模型从结合上面2中模型的特点，并对内存存取和空间进行了优化。在此模型中，non static 数据成员被放置到对象内部，
/// static数据成员， static and nonstatic 函数成员均被放到对象之外。对于虚函数的支持则分两步完成：
/// 1.      每一个class产生一堆指向虚函数的指针，放在表格之中。这个表格称之为虚函数表（virtual table，vtbl）。
/// 2.      每一个对象被添加了一个指针，指向相关的虚函数表vtbl。通常这个指针被称为vptr。vptr的设定（setting）
/// 和重置（resetting）都由每一个class的构造函数，析构函数和拷贝赋值运算符自动完成。
///
/// 另外，虚函数表地址的前面设置了一个指向type_info的指针，RTTI（Run Time Type Identification）
/// 运行时类型识别是有编译器在编译器生成的特殊类型信息，包括对象继承关系，对象本身的描述，
/// RTTI是为多态而生成的信息，所以只有具有虚函数的对象在会生成。
///
/// 优点在于它的空间和存取时间的效率
///
/// - 单继承 继承自一个基类，若重写，则替换基类虚函数表；若新建，则在后面添加
/// - 多继承 继承自两个基类同上；若重写两个基类的重名函数，则替换所有的
/// - 虚继承：为解决菱形继承时，虚基类被重复继承，导致二义性
///
///
/// - 公有继承（public）：当一个类派生自公有基类时，基类的公有成员也是派生类的公有成员，
/// 基类的保护成员也是派生类的保护成员，基类的私有成员不能直接被派生类访问，但是可以通过调用基类的公有和保护成员来访问。
/// - 保护继承（protected）： 当一个类派生自保护基类时，基类的公有和保护成员将成为派生类的保护成员。
/// - 私有继承（private）：当一个类派生自私有基类时，基类的公有和保护成员将成为派生类的私有成员。
///
///- 纯虚函数可以设计成私有的，不过这样不允许在本类之外的非友元函数中直接调用它，子类中只有覆盖这种纯虚函数的义务，却没有调用它的权利。
///



using namespace  std;
class Base
{
public:

    Base(int i) :baseI(i){    cout<<"init "<<__func__<<endl;};

    virtual void print(void){ cout << "调用了虚函数 Base::print()"<<endl; }

    virtual void setI(){cout<<"调用了虚函数 Base::setI()"<<endl;}

    virtual void callFunc(){cout<<"调用了虚函数 Base::callFunc()"<<endl;
                            print();
                           }

    virtual void changePrivate(){cout<<"调用了虚函数 Base::changePrivate()"<<endl;}


    virtual ~Base(){}

private:

    int baseI;

};
class BaseB:public Base{
public:
  BaseB(int i):Base(i){
    cout<<"init "<<__func__<<endl;

  }
  virtual ~BaseB(){}

  virtual void print(void){ cout << "调用了虚函数 BaseB::print()"<<endl;
                            Base::print();
                            Base::setI();
                          }
  virtual void setI(){cout<<"调用了虚函数 BaseB::setI()"<<endl;}

  private:
  virtual void changePrivate(){
    cout<<"调用了虚函数 BaseB::changePrivate()"<<endl;}

};


void printAddr();

/// - 基类的某一函数中使用被子类重载的函数，运行时该函数调用的是哪一个
///  运行的的=是被重载后的函数
/// - 公有切换成私有 可行
/// - 被覆盖的含调用未被覆盖的函数 可行
///  - 盛基类本身维护了一个函数表，子类重写时并不会影响基类的函数表
void overLoad();


int main(int argc, char *argv[])
{
  BaseB b(13);
//  b.callFunc();
//  b.setI();
  b.print();
//b.changePrivate();

  return 0;
}





void overLoad(){


}

void printAddr(){
  //  我们把虚表指针的值取出来： ＊(int＊)(&b)，它是一个地址，虚函数表的地址
  //  把虚函数表的地址强制转换成 int* : ( int ＊) ＊( int＊ )( &b )
  //  再把它转化成我们Fun指针类型 ： (Fun )＊(int ＊)＊(int＊)(&b)

  Base b(1000);
  int * vptrAdree = (int *)(&b);
  cout << "虚函数指针（vprt）的地址是：\t"<<vptrAdree << endl;

  typedef void(*Fun)(void);
  Fun vfunc = (Fun)*( (int *)*(int*)(&b));
  cout << "第一个虚函数的地址是：" << (int *)*(int*)(&b) << endl;
  cout << "通过地址，调用虚函数Base::print()：";
  vfunc();

}

