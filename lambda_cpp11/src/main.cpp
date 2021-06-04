#include <iostream>
#include <algorithm>

/// http://c.biancheng.net/view/7818.html
/// [外部变量访问方式说明符] (参数) mutable noexcept/throw(ex) -> 返回值类型
/// {
/// 函数体;
/// };
///
/// 在 lambda 表达式内可以使用任意一个全局变量，必要时还可以直接修改它们的值
///
/// 为其手动设置一个名称
///     auto display = [](int a,int b) -> void{cout << a << " " << b;};


using namespace std;

int all_num = 0;

int main(int argc, char *argv[])
{

  {
    int num[4] = {4, 2, 3, 1};
    //对 a 数组中的元素进行排序
    sort(num, num+4, [=](int x, int y) -> bool{ return x < y; } );
    for(int n : num){
        cout << n << " ";
    }
  }



  {
    //局部变量
    int num_1 = 1;
    int num_2 = 2;
    int num_3 = 3;
    cout << "lambda1:\n";
    auto lambda1 = [=]{
        //全局变量可以访问甚至修改
        all_num = 10;
        //函数体内只能使用外部变量，而无法对它们进行修改
        cout << num_1 << " "
             << num_2 << " "
             << num_3 << endl;
    };
    lambda1();
    cout << all_num <<endl;
    cout << "lambda2:\n";
    auto lambda2 = [&]{
        all_num = 100;
        num_1 = 10;
        num_2 = 20;
        num_3 = 30;
        cout << num_1 << " "
             << num_2 << " "
             << num_3 << endl;
    };
    lambda2();
    cout << all_num << endl;
  }


  //如果lambda函数抛出非指定异常会使程序崩溃
  {
    auto except1 = []()noexcept{
        throw 100;
    };
    auto except2 = []()throw(char){
        throw 10;
    };
    try{
        except1();
        except2();
    }catch(int){
        cout << "捕获到了整形异常"<< endl;
    }

  }

  return 0;
}
