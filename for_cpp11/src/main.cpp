#include <iostream>
#include <vector>
#include <map>



/// 新的for语法
//for (declaration : expression){
//    //循环体
//}

/// 遍历序列的变量都表示的是当前序列中的各个元素,并不是迭代器
/// 基于范围的 for 循环可以遍历普通数组、string字符串、容器以及初始化列表
/// 基于范围的 for 循环不支持遍历函数返回的以指针形式表示的数组，因为没有明确范围
/// 当基于范围的 for 循环遍历的是某函数返回的 string 对象或者容器时，整个遍历过程中，函数只会执行一次
/// 基于范围的 for 循环完成对容器的遍历，其底层也是借助容器的迭代器实现的
using  namespace std;

int main(int argc, char *argv[])
{

  char arc[] = "http://c.biancheng.net/cplus/11/";
  //for循环遍历普通数组
  for (char ch : arc) {
      cout << ch;
  }
  cout << '!' << endl;
  vector<char>myvector(arc, arc + 23);
  //for循环遍历 vector 容器
  for (auto ch : myvector) {
      cout << ch;
  }
  cout << '!'<<endl;



  for (int num : {1, 2, 3, 4, 5}) {
      cout << num << " ";
  }

  {
    char arc[] = "abcde";
    vector<char>myvector(arc, arc + 5);
    //for循环遍历并修改容器中各个字符的值
    for (auto &ch : myvector) {
        ch++;
    }


    //for循环遍历输出容器中各个字符
    for ( auto ch : myvector) {
        cout << ch;
    }
  }


  {
    map<string, string>mymap{ {"C++11","http://c.biancheng.net/cplus/11/"},
                              {"Python","http://c.biancheng.net/python/"},
                              {"Java","http://c.biancheng.net/java/"} };
    for (pair<string,string> ch : mymap) {
        cout << ch.first << " " << ch.second << endl;
    }



  }

  return 0;

}
