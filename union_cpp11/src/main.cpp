#include <iostream>
#include <string.h>
#include <malloc.h>

///
/// 在一个联合体内，我们可以定义多个不同类型的成员，这些成员将会共享同一块内存空间
/// 与c相比去除了一些限制
/// C++11 标准规定，任何非引用类型都可以成为联合体的数据成员，这种联合体也被称为非受限联合体
/// -  C++11 允许非 POD 类型
/// - C++11 允许联合体有静态成员
///


//POD 类型一般具有以下几种特征（包括 class、union 和 struct等）
//其实POD本质就是与c兼容的数据类型。

//1) 没有用户自定义的构造函数、析构函数、拷贝构造函数和移动构造函数。
//2) 不能包含虚函数和虚基类。
//3) 非静态成员必须声明为 public。
//4) 类中的第一个非静态成员的类型与其基类不同，例如：
//class B1{};
//class B2 : B1 { B1 b; };
//class B2 的第一个非静态成员 b 是基类类型，所以它不是 POD 类型。
//5) 在类或者结构体继承时，满足以下两种情况之一：
//派生类中有非静态成员，且只有一个仅包含静态成员的基类；
//基类有非静态成员，而派生类没有非静态成员。
//我们来看具体的例子：
//class B1 { static int n; };
//class B2 : B1 { int n1; };
//class B3 : B2 { static int n2; };
//对于 B2，派生类 B2 中有非静态成员，且只有一个仅包含静态成员的基类 B1，所以它是 POD 类型。
//对于 B3，基类 B2 有非静态成员，而派生类 B3 没有非静态成员，所以它也是 POD 类型。
//6) 所有非静态数据成员均和其基类也符合上述规则（递归定义），也就是说 POD 类型不能包含非 POD 类型的数据。
//7) 此外，所有兼容C语言的数据类型都是 POD 类型（struct、union 等不能违背上述规则）。


/// 使用注意事项
/// 【自定义的构造函数失效】
/// C++11 规定，如果非受限联合体内有一个非 POD 的成员，而该成员拥有自定义的构造函数，
/// 那么这个非受限联合体的默认构造函数将被编译器删除；
/// 其他的特殊成员函数，例如默认拷贝构造函数、拷贝赋值操作符以及析构函数等，也将被删除
/// 解决上面问题的一般需要用到 placement new

#include <string>
using namespace std;
union U {
    string s;
    int n;
public:
    U() { new(&s) string; }
    ~U() { s.~string(); }
};

///placement new 是 new 关键字的一种进阶用法，既可以在栈（stack）上生成对象，也可以在堆（heap）上生成对象。
/// 相对应地，我们把常见的 new 的用法称为 operator new，它只能在 heap 上生成对象
///

/// 应用 枚举式类
/// 非受限联合体也可以匿名，而当非受限的匿名联合体运用于类的声明时，这样的类被称为“枚举式类”


class Student{
public:
    Student(bool g, int a): gender(g), age(a){}
    bool gender;
    int age;
};
class Singer {
public:
    enum Type { STUDENT, NATIVE, FOREIGENR };
    Singer(bool g, int a) : s(g, a) { t = STUDENT; }
    Singer(int i) : id(i) { t = NATIVE; }
    Singer(const char* n, int s) {
        int size = (s > 9) ? 9 : s;
        memcpy(name , n, size);
        name[s] = '\0';
        t = FOREIGENR;
    }
    ~Singer(){}
private:
    Type t;
    union {
        Student s;
        int id;
        char name[10];
    };
};

int main(int argc, char *argv[])
{
  U u;

  Singer(true, 13);
  Singer(310217);
  Singer("J Michael", 9);

  return 0;
}
