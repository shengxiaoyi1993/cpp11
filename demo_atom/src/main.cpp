//#include <iostream>
//#include <atomic>
#include <type_traits>
#include <iostream>


/// atomic 不可复制和移动
/// atomic<> 是standard layout struct  一个类是Standard Layout类，那么该类的对象在内存上的分配是连续的


/// 为什么一个类同时定义了拷贝构造函数/拷贝赋值函数/移动构造函数/移动赋值函数,
/// 使用is_move_constructible/is_move_assignable/is_copy_constructible/is_copy_assignable进行测试时
/// is_copy_constructible/is_copy_assignable值为false

/// 实例化要求
/// 可复制构造 (CopyConstructible) 及可复制赋值 (CopyAssignable)

//struct StA{
//  int __a;
//  int __b;
//public:
//  StA(int v_a,int v_b):
//    __a(v_a),__b(v_b)
//  {

//  }
//  StA():
//    __a(0),__b(0)
//  {

//  }

//};



//int main(int argc, char *argv[])
//{
//  std::atomic<StA> atA(StA(0,0));
//  atA.store(StA(1,2));
//  std::cout<<"__a:"<<atA.load().__a<<std::endl;
//  std::cout<<"__b:"<<atA.load().__b<<std::endl;



//  return 0;
//}

//#include <thread>
//#include <string>
//#include <chrono>
//#include <mutex>
//#include <atomic>
//using namespace std;

//const int N = 100000000;
////int num = 0;
////atomic_int num(0);
////atomic_int num{0};
//atomic_int num = {0};

//void run()
//{
//  for (int i = 0; i < N; i++) {
//    num++;
//  }
//}

//int main()
//{
//  clock_t start = clock();
//  thread t1(run);
//  thread t2(run);
//  t1.join();
//  t2.join();
//  clock_t end = clock();
//  cout << "num=" << num << ", 用时" << end - start << " ms" << endl;
//    return 0;
//}

//#include<thread>
//#include<iostream>
//#include<mutex>
//using namespace std;

//mutex m;
//const int N=1e8;
//int n;

//void increase_n()
//{
//    for(int i=0;i<N;i++)
//    {
//        m.lock();
//        ++n;
//        m.unlock();
//    }
//}

//int main()
//{
//    thread t1(increase_n);
//    thread t2(increase_n);

//    t1.join();
//    t2.join();

//    cout<<n<<endl;
//    return 0;
//}

//#include<thread>
//#include<iostream>
//#include<atomic>
//using namespace std;

//const int N=1e8;
//atomic<int> n(0);

//void increase_n()
//{
//    for(int i=0;i<N;i++)
//    {
//        ++n;
//    }
//}

//int main()
//{
//    thread t1(increase_n);
//    thread t2(increase_n);

//    t1.join();
//    t2.join();

//    cout<<n<<endl;
//    return 0;
//}



//#include "atomic.hpp"
#include <iostream>
#include <atomic>
#include <vector>
#include <thread>
#include <sstream>

namespace atomic {

// reference: http://www.cplusplus.com/reference/atomic/atomic/atomic/
std::atomic<bool> ready(false);
// atomic_flag::atomic_flag: Constructs an atomic_flag object
// The atomic_flag is in an unspecified state on construction (either set or clear),
// unless it is explicitly initialized to ATOMIC_FLAG_INIT.
std::atomic_flag winner = ATOMIC_FLAG_INIT;

void count1m(int id)
{
  /// yield
  /// 当前线程放弃执行
  /// 避免了空循环，在一定程度上，可以提高cpu的利用率
  /// 事件是以cpu的单个操作的时间片为单位
  while (!ready) { std::this_thread::yield(); }      // wait for the ready signal
  for (volatile int i = 0; i < 1000000; ++i) {}          // go!, count to 1 million
  //  atomically sets the flag to true and obtains its previous value
  /// winner 初始值被设置为false,调用一次test_and_set后被设置成true,因此只有第一次调用时会判断正确
  if (!winner.test_and_set()) { std::cout << "thread #" << id << " won!\n"; }
};

int test_atomic_atomic()
{
  // atomic::atomic: Constructs an atomic object
  std::vector<std::thread> threads;
  std::cout << "spawning 10 threads that count to 1 million...\n";
  for (int i = 1; i <= 10; ++i) threads.push_back(std::thread(count1m, i));
  ready = true;
  for (auto& th : threads) th.join();

  return 0;
}

// reference: http://www.cplusplus.com/reference/atomic/atomic/compare_exchange_weak/
// a simple global linked list:
struct Node { int value; Node* next; };
std::atomic<Node*> list_head(nullptr);

void append(int val)
{     // append an element to the list
  Node* oldHead = list_head;
  Node* newNode = new Node{ val, oldHead };

  std::cout<<"on newNode->next:"<<newNode->next<<" oldHead:"<<oldHead<<std::endl;

  //  std::cout<<val<<":"<<newNode<<std::endl;
  //  std::cout<<val<<":"<<list_head<<std::endl;

  // what follows is equivalent to: list_head = newNode, but in a thread-safe way:
  /// atomically compares the value of the atomic object with non-atomic argument
  /// and performs atomic exchange if equal or atomic load if not
  /// atomic 对象与 非atmoic对象的比较
  /// 参数会要求在这里传入期待的数值和新的数值。它们对比变量的值和期待的值是否一致，
  /// 如果是，则替换为用户指定的一个新的数值。

  while (!list_head.compare_exchange_weak(oldHead, newNode))
  {

    std::cout<<"in newNode->next:"<<newNode->next<<" oldHead:"<<oldHead<<std::endl;

    //    std::cout<<"oldHead:"<<oldHead<<std::endl;
    newNode->next = oldHead;
    //    std::cout<<val<<std::endl;
  }
  //  std::cout<<oldHead<<std::endl;

}


/// list_head 三种状态
/// 初始 取值 compare_exchange_weak(old/new)
/// old=nullptr
///

int test_atomic_compare_exchange_weak()
{
  // atomic::compare_exchange_weak: Compares the contents of the atomic object's contained value with expected:
  // -if true, it replaces the contained value with val(like store).
  // - if false, it replaces expected with the contained value
  // spawn 10 threads to fill the linked list:
  std::vector<std::thread> threads;
  for (int i = 0; i<10; ++i) threads.push_back(std::thread(append, i));
  for (auto& th : threads) th.join();

  // print contents:
  for (Node* it = list_head; it != nullptr; it = it->next)
    std::cout << ' ' << it->value;
  std::cout << '\n';

  // cleanup:
  Node* it; while (it = list_head) { list_head = it->next; delete it; }

  return 0;
}

///
// reference: http://www.cplusplus.com/reference/atomic/atomic/exchange/
std::atomic<bool> winner_(false);

void count1m_(int id)
{
  while (!ready) {}                  // wait for the ready signal
  for (int i = 0; i<1000000; ++i) {}   // go!, count to 1 million
  if (!winner_.exchange(true)) { std::cout << "thread #" << id << " won!\n"; }
};

int test_atomic_exchange()
{
  // atomic::exchange: Replaces the contained value by val and returns the value it had immediately before
  std::vector<std::thread> threads;
  std::cout << "spawning 10 threads that count to 1 million...\n";
  for (int i = 1; i <= 10; ++i) threads.push_back(std::thread(count1m_, i));
  ready = true;
  for (auto& th : threads) th.join();

  return 0;
}


// reference: http://www.cplusplus.com/reference/atomic/atomic/load/
std::atomic<int> foo(0);

void set_foo(int x)
{
  foo.store(x, std::memory_order_relaxed);     // set value atomically
}

void print_foo()
{
  int x;
  do {
    x = foo.load(std::memory_order_relaxed);  // get value atomically
    std::cout << "in foo: " << x << '\n';
  } while (x == 0);
  std::cout << "foo: " << x << '\n';
}

int test_atomic_load()
{
  // atomic::load: Returns the contained value.
  // The operation is atomic and follows the memory ordering specified by sync.
  std::thread first(print_foo);
  std::thread second(set_foo, 10);
  first.join();
  second.join();

  return 0;
}


// reference: http://www.cplusplus.com/reference/atomic/atomic/operator=/
std::atomic<int> foo_ { 0};

void set_foo_(int x)
{
  foo_ = x;
}

void print_foo_()
{
  while (foo_ == 0) {             // wait while foo_=0
    std::this_thread::yield();
  }
  std::cout << "foo_: " << foo_ << '\n';
}

int test_atomic_operator()
{
  // atomic::operator=: Replaces the stored value by val.
  // This operation is atomic and uses sequential consistency (memory_order_seq_cst).
  // To modify the value with a different memory ordering
  std::thread first(print_foo_);
  std::thread second(set_foo_, 10);
  first.join();
  second.join();

  return 0;
}

///
// reference: http://www.cplusplus.com/reference/atomic/atomic/store/
int test_atomic_store()
{
  // atomic::store: Replaces the contained value with val.
  // The operation is atomic and follows the memory ordering specified by sync.
  std::thread first(print_foo);
  std::thread second(set_foo, 10);
  first.join();
  second.join();

  return 0;
}


// reference: http://www.cplusplus.com/reference/atomic/atomic_flag/clear/
std::atomic_flag lock_stream = ATOMIC_FLAG_INIT;
std::stringstream stream;

void append_number(int x)
{
  while (lock_stream.test_and_set()) {}
  stream << "thread #" << x << '\n';
  lock_stream.clear();
}

int test_atomic_flag_atomic_clear()
{
  // atomic_flag::clear: Clears the atomic_flag (i.e., sets it to false)
  //Clearing the atomic_flag makes the next call to member atomic_flag::test_and_set on this object return false.
  // The operation is atomic and follows the memory ordering specified by sync.

  // atomic_flag::test_and_set: Sets the atomic_flag and returns whether it was already set immediately before the call
  // The entire operation is atomic (an atomic read-modify-write operation): the value is not affected by other threads
  // between the instant its value is read (to be returned) and the moment it is modified by this function.
  std::vector<std::thread> threads;
  for (int i = 1; i <= 10; ++i) threads.push_back(std::thread(append_number, i));
  for (auto& th : threads) th.join();

  std::cout << stream.str();
  return 0;
}

} // namespace atomic


void test_for()
{
  std::vector<int> list={1,2,3};
  for (auto it:list) {
    std::cout<<it<<" ";
  }
  std::cout<<std::endl;


  for (auto& it:list) {
    it=888;
  }

  for (auto it:list) {
    std::cout<<it<<" ";
  }
  std::cout<<std::endl;

  for (const auto &it:list) {
    std::cout<<it<<" ";
  }
  std::cout<<std::endl;


}



#include<iostream>
using namespace std;

class A{
public:
  A(){
    this->num = new int(10);
    cout << "构造函数" << endl;
  }
  A(const A&x){
    this->num = new int(*x.num);
    cout << "拷贝构造函数" << endl;
  }
  A(A&&x){
    this->num = x.num;
    x.num = nullptr;
    cout << "移动构造函数" << endl;
  }

  void operator = (A && x){
    this->num = x.num;
    x.num = nullptr;
    cout << "移动赋值函数" << endl;
  }
  void operator = (const A & x){
    this->num = new int(*x.num);
    cout << "operator=" << endl;
  }
  ~A(){
    cout << "析构函数" << endl;
  }
  int *num;
};

void test(){
  A a;
  ///使用拷贝构造函数
  A b=a;
  ///使用拷贝构造函数
  A ba(a);
  /// 使用移动够构造函数
  A c(move(a));
  A ca=move(b);


  A f;

  A d;
  /// 拷贝赋值
  d = f;
  A e;
  /// 移动赋值

//  A g=(e = move(f));
  /// 等式无返回值





  std::cout << "int: "
            << std::is_move_constructible<int>::value
            << std::endl;

  std::cout << "A is_move_constructible: "
            << std::is_move_constructible<A>::value
            << std::endl;

  std::cout << "A is_copy_constructible: "
            << std::is_copy_constructible<A>::value
            << std::endl;

  std::cout << "A is_copy_assignable: "
            << std::is_copy_assignable<A>::value
            << std::endl;
  std::cout << "A is_move_assignable: "
            << std::is_move_assignable<A>::value
            << std::endl;

//    std::cout << "A is_trivially_copyable: "
//         << std::is_trivially_copyable<A>::value
//         << std::endl;


//      std::cout << "A is_trivially_copyable: "
//           << std::is_trivially_copyable<int>::value
//           << std::endl;

}


struct AA {
    int m;
};

struct BB {
    BB(const BB&) {}
};

struct CC {
    virtual void foo();
};



void test_string_trait();


int main(int argc, char *argv[])
{
  //  atomic::test_atomic_atomic();
  //  atomic::test_atomic_compare_exchange_weak();
  //    atomic::test_atomic_load();
  //  atomic::test_atomic_flag_atomic_clear();
  test_for();


  std::vector<int> list={1,4};
  std::vector<int> list_0=list;
  std::vector<int> list_1(list);

  std::vector<int> list_2;
  list_2=list;

  //  std::atomic<std::vector<int>> atom_list;

test();


  std::cout << "int: "
            << std::is_move_constructible<int>::value
            << std::endl;

  std::cout << "std::vector<int> is_move_constructible: "
            << std::is_move_constructible<std::vector<int>>::value
            << std::endl;

  std::cout << "std::vector<int> is_copy_constructible: "
            << std::is_copy_constructible<std::vector<int>>::value
            << std::endl;

  std::cout << "std::vector<int> is_copy_assignable: "
            << std::is_copy_assignable<std::vector<int>>::value
            << std::endl;
  std::cout << "std::vector<int> is_move_assignable: "
            << std::is_move_assignable<std::vector<int>>::value
            << std::endl;


//    std::cout << "std::vector<int> is_trivially_copyable: "
//         << std::is_trivially_copyable<std::vector<int>>::value
//         << std::endl;

//  std::cout << std::boolalpha;
//  std::cout << std::is_trivially_copyable<AA>::value << '\n';
//  std::cout << std::is_trivially_copyable<BB>::value << '\n';
//  std::cout << std::is_trivially_copyable<CC>::value << '\n';

  test_string_trait();

  return 0;

}



void test_string_trait()
{

  std::cout << "std::string: "
            << std::is_move_constructible<std::string>::value
            << std::endl;

  std::cout << "std::vector<std::string> is_move_constructible: "
            << std::is_move_constructible<std::vector<std::string>>::value
            << std::endl;

  std::cout << "std::vector<std::string> is_copy_constructible: "
            << std::is_copy_constructible<std::vector<std::string>>::value
            << std::endl;

  std::cout << "std::vector<std::string> is_copy_assignable: "
            << std::is_copy_assignable<std::vector<std::string>>::value
            << std::endl;
  std::cout << "std::vector<std::string> is_move_assignable: "
            << std::is_move_assignable<std::vector<std::string>>::value
            << std::endl;

}


