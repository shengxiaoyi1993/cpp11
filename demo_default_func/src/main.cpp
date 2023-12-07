#include <iostream>
#include <map>
#include <functional>

/// 在编译期间自动推导出变量的类型

struct divide
{
  int operator()(int a,int b){
    return a/b; }
};

int add(int a,int b)
{
  return a+b;
}


//template<typename T,typename P>
//std::map<std::string,T>

int main(int argc, char *argv[])
{
  std::cout<<"hello !"<<std::endl;

  {
    std::map<std::string,std::function<int(int,int)>> binpos=
    {
    {"+",add},
    {"-",std::minus<int>()}, //标准库函数对象
    {"/",divide()}, //用户定义的函数对象 {"%",mod}, //命名的lambda表达式
    {"*",[](int a,int b){return a*b;}} //未命名的lambda表达式
  };
    std::cout<<"binops[\"+\"](1,2):"<<binpos["+"](1,2)<<std::endl;

  }

  {
    std::map<std::string,std::function<int(int,int)>> binpos;
    //        binpos["+"]=add;
    binpos.insert(std::make_pair<>("+",add));
    binpos.insert({"+",add});

  }


  {
    std::function<int(int,int)> f1 = add;
    std::cout<<f1(12,7)<<std::endl;

  }



  return 0;
}
