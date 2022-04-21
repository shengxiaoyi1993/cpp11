#include <iostream>

/// decltype
/// - 在编译期间自动推导出变量的类型
/// - decltype(exp) varname = value;
/// - auto 根据=右边的初始值 value 推导出变量的类型，而 decltype 根据 exp 表达式推导出变量的类型，跟=右边的 value 没有关系
/// - 原则上讲，exp 就是一个普通的表达式，它可以是任意复杂的形式，但是我们必须要保证 exp 的结果是有类型的，不能是 void
/// - decltype 不要求初始化
/// - 对于cv限定符 「cv 限定符」是 const 和 volatile 关键字的统称：
/// decltype 会保留 cv 限定符，而 auto 有可能会去掉 cv 限定符。
/// 以下是 auto 关键字对 cv 限定符的推导规则：
/// 如果表达式的类型不是指针或者引用，auto 会把 cv 限定符直接抛弃，推导成 non-const 或者 non-volatile 类型。
/// 如果表达式的类型是指针或者引用，auto 将保留 cv 限定符。
/// - 当表达式的类型为引用时，auto 和 decltype 的推导规则也不一样；decltype 会保留引用类型，而 auto 会抛弃引用类型，直接推导出它的原始类型

///
/// - 如果 exp 是一个不被括号( )包围的表达式，或者是一个类成员访问表达式，或者是一个单独的变量，
/// 那么 decltype(exp) 的类型就和 exp 一致，这是最普遍最常见的情况。
/// - 如果 exp 是函数调用，那么 decltype(exp) 的类型就和函数返回值的类型一致
/// - 如果 exp 是一个左值，或者被括号( )包围，那么 decltype(exp) 的类型就是 exp 的引用；
/// 假设 exp 的类型为 T，那么 decltype(exp) 的类型就是 T&。
///
/// 左值/右值
/// 左值是指那些在表达式执行结束后依然存在的数据，也就是持久性的数据；
/// 右值是指那些在表达式执行结束后不再存在的数据，也就是临时性的数据。
/// 有一种很简单的方法来区分左值和右值，对表达式取地址，如果编译器不报错就为左值，否则为右值。
///
/// 只能使用decltype
/// auto 只能用于类的静态成员，不能用于类的非静态成员（普通成员），如果我们想推导非静态成员的类型，这个时候就必须使用 decltype 了
#include <typeinfo>

#include <string>
using namespace std;
class Student{
public:
  static int total;
  string name;
  int age;
  float scores;
};
int Student::total = 0;

class Base{
public:
  Base(){}
  int x;
};

int  main(){
  {
    //    int n = 0;
    //    const int &r = n;
    //    Student stu;
    //    decltype(n) a = n;  //n 为 int 类型，a 被推导为 int 类型
    //    decltype(r) b = n;     //r 为 const int& 类型, b 被推导为 const int& 类型
    //    decltype(Student::total) c = 0;  //total 为类 Student 的一个 int 类型的成员变量，c 被推导为 int 类型
    //    decltype(stu.name) url = "http://c.biancheng.net/cplus/";  //total 为类 Student 的一个 string 类型的成员变量， url 被推导为 string 类型
  }

  {
//    //函数声明
//    int& func_int_r(int, char);  //返回值为 int&
//    int&& func_int_rr(void);  //返回值为 int&&
//    int func_int(double);  //返回值为 int
//    const int& fun_cint_r(int, int, int);  //返回值为 const int&
//    const int&& func_cint_rr(void);  //返回值为 const int&&
//    //decltype类型推导
//    int n = 100;
//    decltype(func_int_r(100, 'A')) a = n;  //a 的类型为 int&
//    decltype(func_int_rr()) b = 0;  //b 的类型为 int&&
//    decltype(func_int(10.5)) c = 0;   //c 的类型为 int
//    decltype(fun_cint_r(1,2,3))  x = n;    //x 的类型为 const int &
//    decltype(func_cint_rr()) y = 0;  // y 的类型为 const int&&
  }

  {

//    const Base obj;
//    //带有括号的表达式
//    decltype(obj.x) a = 0;  //obj.x 为类的成员访问表达式，符合推导规则一，a 的类型为 int
//    decltype((obj.x)) b = a;  //obj.x 带有括号，符合推导规则三，b 的类型为 int&。
//    //加法表达式
//    int n = 0, m = 0;
//    decltype(n + m) c = 0;  //n+m 得到一个右值，符合推导规则一，所以推导结果为 int
//    decltype(n = n + m) d = c;  //n=n+m 得到一个左值，符号推导规则三，所以推导结果为 int&
////    return 0;

  }

  //对cv限定符推导规则
  {
//    //非指针非引用类型
//    const int n1 = 0;
//    auto n2 = 10;
//    n2 = 99;  //赋值不报错
//    decltype(n1) n3 = 20;
////    n3 = 5;  //赋值报错
//    //指针类型
//    const int *p1 = &n1;
//    auto p2 = p1;
////    *p2 = 66;  //赋值报错
//    decltype(p1) p3 = p1;
////    *p3 = 19;  //赋值报错
  }

  {
//    int n = 10;
//    int &r1 = n;
//    //auto推导
//    auto r2 = r1;
//    r2 = 20;
//    cout << n << ", " << r1 << ", " << r2 << endl;
//    //decltype推导
//    decltype(r1) r3 = n;
//    r3 = 99;
//    cout << n << ", " << r1 << ", " << r3 << endl;
//    return 0;
  }

  /// get the
  {
    int aint=0;
    cout<<"typeid(int).name():"<<typeid(int).name()<<endl;
    cout<<"typeid(aint).name():"<<typeid(aint).name()<<endl;

    uint auint=0;
    cout<<"typeid(uint).name():"<<typeid(uint).name()<<endl;
    cout<<"typeid(auint).name():"<<typeid(auint).name()<<endl;


    u_int8_t auchar=0;
    cout<<"typeid(auchar).name():"<<typeid(auchar).name()<<endl;
    cout<<"typeid(u_int8_t).name():"<<typeid(u_int8_t).name()<<endl;


    bool abool=0;
    cout<<"typeid(bool).name():"<<typeid(bool).name()<<endl;
    cout<<"typeid(abool).name():"<<typeid(abool).name()<<endl;

    if (std::string(typeid(bool).name()) == "b") {
      std::cout<<"is bool"<<std::endl;
    }

//    int x=static_cast<typeid(abool)>(abool);

    ushort aushort=0;
    cout<<"typeid(ushort).name():"<<typeid(ushort).name()<<endl;
    cout<<"typeid(aushort).name():"<<typeid(aushort).name()<<endl;

    short ashort=0;
    cout<<"typeid(short).name():"<<typeid(short).name()<<endl;
    cout<<"typeid(ashort).name():"<<typeid(ashort).name()<<endl;



    double dint=0.9;
    cout<<"typeid(double).name():"<<typeid(double).name()<<endl;
    cout<<"typeid(dint).name():"<<typeid(dint).name()<<endl;

    std::string astring="sxy";
    cout<<"typeid(std::string).name():"<<typeid(std::string).name()<<endl;
    cout<<"typeid(astring).name():"<<typeid(astring).name()<<endl;

    std::string y=static_cast<std::string>(astring);

    char* astr="sxy";
    cout<<"typeid(char*).name():"<<typeid(char*).name()<<endl;
    cout<<"typeid(astr).name():"<<typeid(astr).name()<<endl;



    Student astu;
    cout<<"typeid(Student).name():"<<typeid(Student).name()<<endl;
    cout<<"typeid(astu).name():"<<typeid(astu).name()<<endl;

  }

  return 0;
}

template <typename T>
class TBase {
public:
    void func(T& container) {
        m_it = container.begin();
    }
private:
    decltype(T().begin()) m_it;
    //注意这里
    //如果传入一个 const 类型的容器，编译器马上就会弹出一大堆错误信息。
    //原因就在于，T::iterator并不能包括所有的迭代器类型，当 T 是一个 const 容器时，应当使用 const_iterator。
};
