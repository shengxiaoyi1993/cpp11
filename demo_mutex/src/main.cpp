#include <iostream>
#include <thread>
#include <mutex>

/// recursive_mutex 允许多级加锁
///

//class X {
//    std::recursive_mutex m;
//    std::string shared;
//  public:
//    void fun1() {
//      std::lock_guard<std::recursive_mutex> lk(m);
//      shared = "fun1";
//      std::cout << "in fun1, shared variable is now " << shared << '\n';
//    }
//    void fun2() {
//      std::lock_guard<std::recursive_mutex> lk(m);
//      shared = "fun2";
//      std::cout << "in fun2, shared variable is now " << shared << '\n';
//      fun1(); // ① 递归锁在此处变得有用
//      std::cout << "back in fun2, shared variable is " << shared << '\n';
//    };
//};

//int main()
//{
//    X x;
//    std::thread t1(&X::fun1, &x);
//    std::thread t2(&X::fun2, &x);
//    t1.join();
//    t2.join();
//    return 0;
//}


//#include <iostream>                // std::cout
//#include <thread>                // std::thread
//#include <mutex>                // std::mutex, std::unique_lock
//#include <condition_variable>    // std::condition_variable


//std::mutex mtx; // 全局互斥锁.
//std::condition_variable cv; // 全局条件变量.
//bool ready = false; // 全局标志位.


//void do_print_id(int id)
//{
//    std::unique_lock <std::mutex> lck(mtx); // 加锁互斥量
//    while (!ready)
//    {
//      std::cout<<"wait"<<std::endl;

//        cv.wait(lck); // 当ready==false的时候，while语句执行到wait这里，然后就堵塞到这行，等到通知信号，同时解锁互斥量，不影响其他线程获取锁。
//    }                 //当 cv.notify_all(); // 唤醒所有线程. 执行到这句wait就收到了信号就被唤醒开始干活，首先就是不断的尝试重新获取并加锁互斥量。
//                      //若获取不到锁就卡在这里反复尝试加锁
//                      //若获取到了锁才往下执行

//    std::cout << "thread " << id << '\n';
//}

//void go()
//{
//    std::unique_lock <std::mutex> lck(mtx);
//    ready = true; // 设置全局标志位为 true.
//    cv.notify_all(); // 唤醒所有线程.
//}

//void test_try_lockwrongmutex();

////void thread_comsume();

//class CP
//{
//public:
//  void start()
//  {
//    __thread_ =std::thread(&CP::_thread_consume,this);
//  }

//  void add()
//  {
//    std::unique_lock<std::mutex> tmplck(__mutex);
//    std::cout<<"in producer process------------------"<<std::endl;
//    std::cout<<"out producer process------------------"<<std::endl;
//  }

//private:
//  std::mutex __mutex;
//  std::thread __thread_;
//  std::condition_variable __condi_;

//private:
//  void _thread_consume()
//  {
//    while (true) {
////     {
//      std::unique_lock<std::mutex> tmplck(__mutex);

//      __condi_.wait_for(tmplck,std::chrono::milliseconds(1000));
////      }

////      std::unique_lock<std::mutex> tmplck(__mutex);
//      std::cout<<"in consumer process+++++++++++++++++++++"<<std::endl;

//      std::this_thread::sleep_for(std::chrono::milliseconds(10000));
//      std::cout<<"out consumer process+++++++++++++++++++++"<<std::endl;

//    }
//    return;
//  }

//};

//void test_cp();

//int main()
//{

////    std::thread threads[10];
////    // spawn 10 threads:

////    threads[0] = std::thread(do_print_id, 0);

////    std::this_thread::sleep_for(std::chrono::milliseconds(1000));

////    ready=true;
////    for (int i = 1; i < 10; ++i)
////        threads[i] = std::thread(do_print_id, i);

////    std::cout << "10 threads ready to race...\n";
//////    go(); // go!

////  for (auto & th:threads)
////        th.join();

////  test_try_lockwrongmutex();

//  test_cp();

//    return 0;
//}

//void test_cp()
//{
//  CP ncp;
//  ncp.start();
//  while (true) {
//    ncp.add();
//    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
//  }
//  return;
//}



///// 假设有锁以指针方式锁定调用
///// 原mutex被释放再次调用时会发生什么
///// 线程锁锁定时,释放线程锁,尝试解锁时会能溃

//static std::mutex *__g_mutex=nullptr;
//static std::mutex __g_mutex_nofree;
//int _g_count=0;

//void do_something()
//{
//  if (_g_count%2 != 0) {
//    _g_count++;
////    std::this_thread::sleep_for(std::chrono::milliseconds(2000));
//    free(__g_mutex);
////    __g_mutex=nullptr;
//  }
//  else{
//    _g_count++;
//    std::unique_lock<std::mutex> lck(*__g_mutex);
//    std::cout<<"do_something:"<<_g_count<<std::endl;
//    std::cout.flush();
//    std::this_thread::sleep_for(std::chrono::milliseconds(5000));
//  }
//}

//void test_try_lockwrongmutex()
//{
//  __g_mutex=new std::mutex;
//  std::thread threads[3];
//      for (int i = 0; i < 3; ++i)
//      {
//        threads[i] = std::thread(do_something);
//        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
//      }


//  for (auto & th:threads)
//        th.join();

//}


#include <iostream>
#include <mutex>
#include <thread>


struct big_object
{
public:
  big_object() {}
  void  prepare_data(int num)
  {
    __num=num;
  }

private:
  int __num;
};

void process_big_object(std::unique_ptr<big_object> p)
{
  std::cout<<""<<std::this_thread::get_id()<<" "<<p.get()<<std::endl;

}

struct Y
{
  double operator()(double v){
    std::cout<<v<<std::endl;
  }
};
#include <future>
class Foo{};

int main(int argc, char *argv[])
{

  {
    Foo some_array[5];
    std::atomic<Foo*> p(some_array);
    Foo* x=p.fetch_add(2);  // p加2，并返回原始值
  //  assert(x==some_array);
  //  assert(p.load()==&some_array[2]);
  //  x=(p-=1);  // p减1，并返回原始值
  //  assert(x==&some_array[1]);
  //  assert(p.load()==&some_array[1]);

  }


  auto f6=std::async(std::launch::async,Y(),1.234);  // 在新线程上执行
//  auto f7=std::async(std::launch::deferred,baz,std::ref(x));  // 在wait()或get()调用时执行
//  auto f8=std::async(
//                std::launch::deferred | std::launch::async,
//                baz,std::ref(x));  // 实现选择执行方式
//  auto f9=std::async(baz,std::ref(x));
//  f7.wait();  //  调用延迟函数
  f6.get();


  /// 硬件 支持的线程数
  std::cout<<"hardware_concurrency:"<<std::thread::hardware_concurrency()<<std::endl;

  std::unique_ptr<big_object> p(new big_object);
  p->prepare_data(42);
  std::thread t(process_big_object,std::move(p));

  std::cout<<"main "<<std::this_thread::get_id()<<" "<<p.get()<<std::endl;

  t.join();


  return 0;
}

/// c++ 未提供现成地读写锁,见boost




