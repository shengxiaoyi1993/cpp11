#include <iostream>

/// 泛型编程时可能碰到函数返回值由参数类型确定，通用的写法较为晦涩，如下
template <typename T, typename U>
decltype((*(T*)0) + (*(U*)0)) add_0(T t, U u)
{
    return t + u;
}
/// 因此，在 C++11 中增加了返回类型后置（trailing-return-type，又称跟踪返回类型）语法，将 decltype 和 auto 结合起来完成返回值类型的推导
template <typename T, typename U>
auto add_1(T t, U u) -> decltype(t + u)
{
    return t + u;
}

/// 若遇到以下情况不得不使用trailing-return-type实现

int& foo(int& i);
float foo(float& f);

template <typename T>
auto func(T& val) -> decltype(foo(val))
{
    return foo(val);
}


int main(int argc, char *argv[])
{
  std::cout<<"hello !"<<std::endl;

  auto z=add_0(1,8);
  std::cout<<"z:"<<z<<std::endl;


  auto s=add_1(1,8.0);
  std::cout<<"s:"<<s<<std::endl;


  return 0;
}
