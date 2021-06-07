#include <iostream>

/// move 本意为 "移动"，但该函数并不能移动任何数据，它的功能很简单，就是将某个左值强制转化为右值。
///  - 通过该转换，用于优先调用以右值引用作为参数的函数
///  - 也可以通过转换，然后转移他拥有的资源的所有权


using namespace std;

class movedemo{
public:
    movedemo():num(new int(0)){
        cout<<"construct!"<<endl;
    }
    //拷贝构造函数
    movedemo(const movedemo &d):num(new int(*d.num)){
        cout<<"copy construct!"<<endl;
    }
    //移动构造函数
    movedemo(movedemo &&d):num(d.num){
        d.num = NULL;
        cout<<"move construct!"<<endl;
    }
public:     //这里应该是 private，使用 public 是为了更方便说明问题
    int *num;
};


class first {
public:
    first() :num(new int(0)) {
        cout << "construct!" << endl;
    }
    //移动构造函数
    first(first &&d) :num(d.num) {
        d.num = NULL;
        cout << "first move construct!" << endl;
    }
public:    //这里应该是 private，使用 public 是为了更方便说明问题
    int *num;
};
class second {
public:
    second() :fir() {}
    //用 first 类的移动构造函数初始化 fir
    second(second && sec) :fir(move(sec.fir)) {
        cout << "second move construct" << endl;
    }
public:    //这里也应该是 private，使用 public 是为了更方便说明问题
    first fir;
};



int main(){
    movedemo demo;
    cout << "demo2:\n";
    movedemo demo2 = demo;
    //cout << *demo2.num << endl;   //可以执行
    cout << "demo3:\n";
    movedemo demo3 = std::move(demo);
    //此时 demo.num = NULL，因此下面代码会报运行时错误
    //cout << *demo.num << endl;


    {
      second oth;
      second oth2 = move(oth);
    }


    return 0;
}
