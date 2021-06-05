#include <iostream>

/// 基于右值引用引申出的 2 种 C++ 编程技巧，分别为移动语义和完美转发
/// lvalue 是“loactor value”的缩写，可意为存储在内存中、有明确存储地址（可寻址）的数据，
/// 而 rvalue 译为 "read value"，指的是那些可以提供数据值的数据（不一定可以寻址，例如存储于寄存器中的数据）。
///
/// 判断左值和右值
/// 1) 可位于赋值号（=）左侧的表达式就是左值；反之，只能位于赋值号右侧的表达式就是右值。
/// 2）有名称的、可以获取到存储地址的表达式即为左值；反之则是右值。
///
/// C++右值引用
/// C++98/03 标准中 编译器允许我们为 num 左值建立一个引用，但不可以为 10 这个右值建立引用。又称为左值引用
/// 注意，虽然 C++98/03 标准不支持为右值建立非常量左值引用，但允许使用常量左值引用操作右值。也就是说，常量左值引用既可以操作左值，也可以操作右值
//int num = 10;
//const int &b = num;
//const int &c = 10;
/// C++11 标准新引入了另一种引用方式，称为右值引用，用 "&&" 表示。
///
//int num = 10;
////int && a = num;  //右值引用不能初始化为左值
//int && a = 10;
/// 另外值得一提的是，C++ 语法上是支持定义常量右值引用的
///
///
/// 对于类的内部包含盛堆空间的数据
//construct!                <-- 执行 demo()
//copy construct!       <-- 执行 return demo()
//class destruct!         <-- 销毁 demo() 产生的匿名对象
//copy construct!       <-- 执行 a = get_demo()
//class destruct!         <-- 销毁 get_demo() 返回的临时对象
//class destruct!         <-- 销毁 a
/// 右值引用的语法，借助它可以实现移动语义
/// 指的就是以移动而非深拷贝的方式初始化含有指针成员的类对象。
/// 简单的理解，移动语义指的就是将其他对象（通常是临时对象）拥有的内存资源“移为已用”。
/// 为了满足用户使用左值初始化同类对象时也通过移动构造函数完成的需求，新引入了 std::move() 函数，
/// 它可以将左值强制转换成对应的右值，由此便可以使用移动构造函数


using namespace std;

//class demo{
//public:
//   demo():num(new int(0)){
//      cout<<"construct!"<<endl;
//   }
//   //拷贝构造函数
//   demo(const demo &d):num(new int(*d.num)){
//      cout<<"copy construct!"<<endl;
//   }
//   ~demo(){
//      cout<<"class destruct!"<<endl;
//   }
//private:
//   int *num;
//};
//demo get_demo(){
//    return demo();
//}


class demo{
public:
    demo():num(new int(0)){
        cout<<"construct!"<<endl;
    }
    demo(const demo &d):num(new int(*d.num)){
        cout<<"copy construct!"<<endl;
    }
    //添加移动构造函数
    demo(demo &&d):num(d.num){
        d.num = NULL;
        cout<<"move construct!"<<endl;
    }
    ~demo(){
        cout<<"class destruct!"<<endl;
    }
private:
    int *num;
};
demo get_demo(){
    return demo();
}


int main(int argc, char *argv[])
{

  {
    int && a = 10;
    const int &c = 10;

    a = 100;
    cout << a << endl;
    cout << c << endl;

    const int&& aa = 10;
    cout << aa << endl;

  }

  {
    demo a = get_demo();
    return 0;
  }
  return 0;
}
