#include <iostream>
#include <map>

///  typedef 重定义类型是很方便的，但它也有一些限制，比如，无法重定义一个模板

/// typedef 重定义模板需要使用外敷类
/// 在复用某些泛型代码时非常难受




template <typename Val>
struct str_map
{
    typedef std::map<std::string, Val> type;
};
// ...
str_map<int>::type map1;
// ...

/// using在重定义普通类型上，两种使用方法的效果是等价的，唯一不同的是定义语法。
/// c++11 使用新的 using 别名语法定义了 std::map 的模板别名 str_map_t （alias template）
template <typename Val>
using str_map_t = std::map<std::string, Val>;
// ...


int main(int argc, char *argv[])
{
//  std::cout<<"hello !"<<std::endl;
  str_map_t<int> map0;


  return 0;
}
