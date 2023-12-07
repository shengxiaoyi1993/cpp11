#include <iostream>
#include <vector>
#include <map>
#include <list>
#include <algorithm>
#include <assert.h>
#include <memory>
#include <thread>
#include <queue>




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




  {
    std::map<std::string,std::vector<int>> map0;
    map0["a"]={0,1,2,3};
    {
      std::vector<int> list=map0["a"];
      for(auto&it:list)
      {
        it+=1;
      }

      for(auto&it:list)
      {
        std::cout<<it<<std::endl;
      }

      for(auto&it:map0["a"])
      {
        std::cout<<it<<std::endl;
      }
    }
    std::cout<<"---------------"<<std::endl;


    {
      std::vector<int>& list=map0["a"];
      for(auto&it:list)
      {
        it+=1;
      }

      for(auto&it:list)
      {
        std::cout<<it<<std::endl;
      }

      for(auto&it:map0["a"])
      {
        std::cout<<it<<std::endl;
      }
    }
    return 0;
  }

  {
    std::queue<int> num_queue;
    for (int var = 0; var < 100; ++var) {
      num_queue.push(var);
      if (num_queue.size()>10) {
        num_queue.pop();
      }
      std::cout<<"num_queue.size:"<<num_queue.size()<<std::endl;
    }
    return 0;
  }



  {
    std::vector<std::pair<int,std::shared_ptr<int>>> list;
    list.push_back({0,std::shared_ptr<int>()});
    std::cout<<"list[0].second:"<<list[0].second.get()<<std::endl;

    std::shared_ptr<int> pnum(new int[10]);
    list[0].second.swap(pnum);
//    list[0].second.swap(std::shared_ptr<int>(new int[20]));

    list.push_back({0,std::shared_ptr<int>()});
    std::cout<<"list[0].second:"<<list[0].second.get()<<std::endl;




//    list[0].second=std::sha<int*>(new int[10]);

//    list[0].second=std::make_shared<int*>(new int[10]);
//    list[0].second=std::make_shared<int>(10);
//    std::cout<<"list[0].second:"<<*(list[0].second.get())<<std::endl;

//    std::

    std::shared_ptr<int> p2(nullptr);
    p2 = std::make_shared<int>(10);
    std::cout<<"p2:"<<*(p2.get())<<std::endl;
  }
//  static_assert(sizeof (int) == 4,"");


  {
    std::list<int> list_num;
    list_num.push_back(0);
    list_num.push_back(10);
    list_num.push_back(100);
    list_num.push_back(1000);
    list_num.push_back(10000);
    for (auto &it:list_num) {
      std::cout<<" "<<it;
    }
    std::cout<<std::endl;

    auto pos_find_10=std::find(list_num.begin(),list_num.end(),10);
    auto pos_find_1000=std::find(list_num.begin(),list_num.end(),1000);
    auto pos_end=list_num.end();

    auto pos_find=std::find(list_num.begin(),list_num.end(),100);
    if (pos_find!= list_num.end()) {
      std::cout<<"erase "<<*pos_find<<std::endl;

      list_num.erase(pos_find);
    }

    for (auto &it:list_num) {
      std::cout<<" "<<it;
    }
    std::cout<<std::endl;
    /// 此处可以验证某一数据在链表中被删除,其他元素的指针未发生改变
    std::cout<<"pos_find_10 "<<*pos_find_10<<std::endl;
    std::cout<<"pos_find_1000 "<<*pos_find_1000<<std::endl;
    std::cout<<"pos_end==list_num.end():"<<(pos_end==list_num.end())<<std::endl;

    list_num.push_back(100000);

    /// 此处可以验证链表中增加某一数据,其他元素的指针未发生改变
    std::cout<<"pos_find_10 "<<*pos_find_10<<std::endl;
    std::cout<<"pos_find_1000 "<<*pos_find_1000<<std::endl;
    std::cout<<"pos_end==list_num.end():"<<(pos_end==list_num.end())<<std::endl;


  }

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


  {
    std::map<int,int> h;

    h[8]++;

    for (auto it:h) {
      std::cout<<"("<<it.first<<","<<it.second<<")"<<std::endl;
    }
  }


  return 0;

}
