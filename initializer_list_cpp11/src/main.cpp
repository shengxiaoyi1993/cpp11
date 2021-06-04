#include <iostream>

/// C++98/03下列表初始化只有普通数组和POD类型

//初始化列表
int i_arr[3] = { 1, 2, 3 };  //普通数组
struct A
{
    int x;
    struct B
    {
        int i;
        int j;
    } b;
} a = { 1, { 2, 3 } };  //POD类型（POD 类型即 plain old data 类型，简单来说，是可以直接使用 memcpy 复制的对象。）
//拷贝初始化（copy-initialization）
int i = 0;
class Foo
{
    public:
    Foo(int) {}
} foo = 123;  //需要拷贝构造函数
//直接初始化（direct-initialization）
int j(0);
Foo bar(123);

/// 在 C++11 中，初始化列表的适用性被大大增加了。它现在可以用于任何类型对象的初始化
/// - a4 和 a6 的写法，是 C++98/03 所不具备的。在 C++11 中，可以直接在变量名后面跟上初始化列表，来进行对象的初始化。
/// - new 操作符等可以用圆括号进行初始化的地方，也可以使用初始化列表
/// - 堆上动态分配的数组终于也可以使用初始化列表进行初始化

class FooF
{
public:
    FooF(int) {}
private:
    FooF(const FooF &);
};

struct FooS
{
    FooS(int, double) {}
};

FooS func(void)
{
    return { 123, 321.0 };
}

int main(int argc, char *argv[])
{
  std::cout<<"hello !"<<std::endl;
  FooF a1(123);
//  FooF a2 = 123;  //error: 'Foo::Foo(const Foo &)' is private
  FooF a3 = { 123 }; //a3 虽然使用了等于号，但它仍然是列表初始化，因此，私有的拷贝构造并不会影响到它
  FooF a4 { 123 };
  int a5 = { 3 };
  int a6 { 3 };
  return 0;

  return 0;
}
