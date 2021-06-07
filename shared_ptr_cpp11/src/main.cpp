#include <iostream>
#include <memory>
/// 1)  通过如下 2 种方式，可以构造出 shared_ptr<T> 类型的空智能指针：
/// 2) 在构建 shared_ptr 智能指针，也可以明确其指向
/// 3) 除此之外，shared_ptr<T> 模板还提供有相应的拷贝构造函数和移动构造函数
/// 4) 在初始化 shared_ptr 智能指针时，还可以自定义所指堆内存的释放规则，这样当堆内存的引用计数为 0 时，会优先调用我们自定义的释放规则

using namespace std;

void deleteInt(int*p) {
    delete []p;
}

int main(int argc, char *argv[])
{

  {
    std::shared_ptr<int> p1;             //不传入任何实参
    std::shared_ptr<int> p2(nullptr);    //传入空指针 nullptr
  }

  {
    std::shared_ptr<int> p3(new int(10));
    std::shared_ptr<int> p4 = std::make_shared<int>(10);
  }

  {
    std::shared_ptr<int> p3(new int(10));

    //调用拷贝构造函数
    std::shared_ptr<int> p4(p3);//或者 std::shared_ptr<int> p4 = p3;
    //调用移动构造函数
    std::shared_ptr<int> p5(std::move(p4)); //或者 std::shared_ptr<int> p5 = std::move(p4);
  }

  {
    //指定 default_delete 作为释放规则
    std::shared_ptr<int> p6(new int[10], std::default_delete<int[]>());
    //自定义释放规则

    //初始化智能指针，并自定义释放规则
    std::shared_ptr<int> p7(new int[10], deleteInt);
    std::shared_ptr<int> p8(new int[10], [](int* p) {delete[]p; });

  }

  //构建 2 个智能指针
  std::shared_ptr<int> p1(new int(10));
  std::shared_ptr<int> p2(p1);
  //输出 p2 指向的数据
  cout << *p2 << endl;
  p1.reset();//引用计数减 1,p1为空指针
  if (p1) {
      cout << "p1 不为空" << endl;
  }
  else {
      cout << "p1 为空" << endl;
  }
  //以上操作，并不会影响 p2
  cout << *p2 << endl;
  //判断当前和 p2 同指向的智能指针有多少个
  cout << p2.use_count() << endl;
  return 0;
}
