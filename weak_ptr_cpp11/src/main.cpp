#include <iostream>
#include <memory>
using namespace std;

/// C++11标准虽然将 weak_ptr 定位为智能指针的一种，
/// 但该类型指针通常不单独使用（没有实际用处），只能和 shared_ptr 类型指针搭配使用
/// 借助 weak_ptr 类型指针， 我们可以获取 shared_ptr 指针的一些状态信息，
/// 比如有多少指向相同的 shared_ptr 指针、shared_ptr 指针指向的堆内存是否已经被释放等等
/// weak_ptr 类型指针并不会影响所指堆内存空间的引用计数

//operator=()	重载 = 赋值运算符，是的 weak_ptr 指针可以直接被 weak_ptr 或者 shared_ptr 类型指针赋值。
//swap(x)	其中 x 表示一个同类型的 weak_ptr 类型指针，该函数可以互换 2 个同类型 weak_ptr 指针的内容。
//reset()	将当前 weak_ptr 指针置为空指针。
//use_count()	查看指向和当前 weak_ptr 指针相同的 shared_ptr 指针的数量。
//expired()	判断当前 weak_ptr 指针为否过期（指针为空，或者指向的堆内存已经被释放）。
//lock()	如果当前 weak_ptr 已经过期，则该函数会返回一个空的 shared_ptr 指针；反之，该函数返回一个和当前 weak_ptr 指向相同的 shared_ptr 指针。

int main(int argc, char *argv[])
{
  std::cout<<"hello !"<<std::endl;

  std::shared_ptr<int> sp1(new int(10));
  std::shared_ptr<int> sp2(sp1);
  std::weak_ptr<int> wp(sp2);
  //输出和 wp 同指向的 shared_ptr 类型指针的数量
  cout << wp.use_count() << endl;
  //释放 sp2
  sp2.reset();
  cout << wp.use_count() << endl;
  //借助 lock() 函数，返回一个和 wp 同指向的 shared_ptr 类型指针，获取其存储的数据
  cout << *(wp.lock()) << endl;

  sp1.reset();

//  cout << *(wp.lock()) << endl;

  return 0;
}
