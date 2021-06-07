#include <iostream>
#include <memory>

/// unique_ptr 指针自然也具备“在适当时机自动释放堆内存空间”的能力。
/// 和 shared_ptr 指针最大的不同之处在于，unique_ptr 指针指向的堆内存无法同其它 unique_ptr 共享
/// 构造方法
/// 同shared_ptr
/// 值得一提的是，和 shared_ptr 指针不同，为 unique_ptr 自定义释放规则，只能采用函数对象的方式。例如：
/// 不支持拷贝构造函数

using namespace std;


struct myDel
{
    void operator()(int *p) {
        delete p;
    }
};

int main(int argc, char *argv[])
{
  ///函数对象的方式实现自定义析构方法
  std::unique_ptr<int, myDel> p6(new int);
  std::unique_ptr<int, myDel> p7(new int, myDel());

  {
    std::unique_ptr<int> p5(new int);
    *p5 = 10;
    // p 接收 p5 释放的堆内存
    int * p = p5.release();
    cout << *p << endl;
    //判断 p5 是否为空指针
    if (p5) {
        cout << "p5 is not nullptr" << endl;
    }
    else {
        cout << "p5 is nullptr" << endl;
    }
    std::unique_ptr<int> p6;
    //p6 获取 p 的所有权
    p6.reset(p);
    cout << *p6 << endl;;
  }

  return 0;
}
