#include <iostream>
#include <memory>
#include <unistd.h>
#include <vector>
/// 1)  通过如下 2 种方式，可以构造出 shared_ptr<T> 类型的空智能指针：
/// 2) 在构建 shared_ptr 智能指针，也可以明确其指向
/// 3) 除此之外，shared_ptr<T> 模板还提供有相应的拷贝构造函数和移动构造函数
/// 4) 在初始化 shared_ptr 智能指针时，还可以自定义所指堆内存的释放规则，
/// 这样当堆内存的引用计数为 0 时，会优先调用我们自定义的释放规则

using namespace std;

void deleteInt(int*p) {
  delete []p;
}


class Node{
public:
  Node():__ptr(nullptr)
  {
    cout<<__func__<<endl;
    __ptr=new char[10];
  }
  ~Node(){
    cout<<__func__<<endl;
    delete[] __ptr;
    __ptr=nullptr;
  }

private:
  char *__ptr;
};


class Factory{
public:
  Factory():__node(nullptr){
    __node=std::shared_ptr<Node>( new Node(),[](Node* p) {
        delete p;
        p=nullptr;
        cout<<__func__<<endl;
  });
  }
  ~ Factory(){
  }

  std::shared_ptr<Node> clone(){
    return __node;
  }


private:
  //  Node *__node;
  std::shared_ptr<Node> __node;             //不传入任何实参


};


class A20230831
{
public:
  A20230831(int& vi_num):__num(vi_num)
  {

  }
  void setNum(const int& v_num)
  {
    __num=v_num;
  }
  void print()
  {
    std::cout<<"__num:"<<__num<<std::endl;
  }
private:
  int & __num;
};


int main(int argc, char *argv[])
{

  {
    int numa=7;
    A20230831 a(numa);
    int num=57;
    a.setNum(num);
    a.print();
    num=88;
    a.print();
    std::cout<<"numa:"<<numa<<std::endl;

  }

  //  {
  //    std::shared_ptr<int> p1;             //不传入任何实参
  //    std::shared_ptr<int> p2(nullptr);    //传入空指针 nullptr
  //  }

  //  {
  //    std::shared_ptr<int> p3(new int(10));
  //    std::shared_ptr<int> p4 = std::make_shared<int>(10);
  //  }

  //  {
  //    std::shared_ptr<Node> p3(new Node());

  //    //调用拷贝构造函数
  //    std::shared_ptr<Node> p4(p3);//或者 std::shared_ptr<int> p4 = p3;
  //    std::cout<<""<<p4.use_count()<<std::endl;
  //    std::cout<<""<<p3.use_count()<<std::endl;


  //    //调用移动构造函数
  //    std::shared_ptr<Node> p5(std::move(p4)); //或者 std::shared_ptr<int> p5 = std::move(p4);
  //    /// p4的数据所有权被转移
  //    std::cout<<""<<p4.use_count()<<std::endl;
  //  }

  while (true)
  {
    //        std::shared_ptr<int> p6(new int[1000], std::default_delete<int[]>());
    std::shared_ptr<int> p6(new int[1000]);

  }


  //  {
  //    //指定 default_delete 作为释放规则
  //    std::shared_ptr<int> p6(new int[10], std::default_delete<int[]>());
  //    //自定义释放规则

  //    //初始化智能指针，并自定义释放规则
  //    std::shared_ptr<int> p7(new int[10], deleteInt);
  //    std::shared_ptr<int> p8(new int[10], [](int* p) {delete[]p; });

  //  }


  //  {
  //    //构建 2 个智能指针
  //    std::shared_ptr<int> p1(new int(10));
  //    std::shared_ptr<int> p2(p1);
  //    //输出 p2 指向的数据
  //    cout << *p2 << endl;
  //    p1.reset();//引用计数减 1,p1为空指针
  //    if (p1) {
  //      cout << "p1 不为空" << endl;
  //    }
  //    else {
  //      cout << "p1 为空" << endl;
  //    }
  //    //以上操作，并不会影响 p2
  //    cout << *p2 << endl;
  //    //判断当前和 p2 同指向的智能指针有多少个
  //    cout << p2.use_count() << endl;
  //  }


  //  std::shared_ptr<Node> c_p(nullptr);             //不传入任何实参


  //  {
  //    Factory factory;

  //    auto c0=factory.clone();

  //    auto c1=factory.clone();

  //    c_p=factory.clone();
  //  }


  ///////////////////////////////////////////////////////////////////////////////
  /// save shared_ptr in list
  /// will element be deleted when list clear element
  //  {
  //    std::shared_ptr<Node> node(new Node());
  //    std::vector< std::shared_ptr<Node>> l_node;
  //    l_node.push_back(node);
  //    l_node.clear();
  //  }


  //  /// when not clear ,not delete
  //  /// when clear, delete
  //  std::vector< std::shared_ptr<Node>> l_node;

  //  {
  //    std::shared_ptr<Node> node(new Node());
  //    l_node.push_back(node);
  //    l_node.clear();
  //  }



  //pause();

  return 0;
}
