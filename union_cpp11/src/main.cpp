#include <iostream>

///
/// 在一个联合体内，我们可以定义多个不同类型的成员，这些成员将会共享同一块内存空间
/// 与c相比去除了一些限制
/// C++11 标准规定，任何非引用类型都可以成为联合体的数据成员，这种联合体也被称为非受限联合体
///


int main(int argc, char *argv[])
{
  std::cout<<"hello !"<<std::endl;

  return 0;
}
