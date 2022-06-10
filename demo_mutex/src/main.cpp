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


#include <iostream>                // std::cout
#include <thread>                // std::thread
#include <mutex>                // std::mutex, std::unique_lock
#include <condition_variable>    // std::condition_variable


std::mutex mtx; // 全局互斥锁.
std::condition_variable cv; // 全局条件变量.
bool ready = false; // 全局标志位.


void do_print_id(int id)
{
    std::unique_lock <std::mutex> lck(mtx); // 加锁互斥量
    while (!ready)
    {
      std::cout<<"wait"<<std::endl;

        cv.wait(lck); // 当ready==false的时候，while语句执行到wait这里，然后就堵塞到这行，等到通知信号，同时解锁互斥量，不影响其他线程获取锁。
    }                 //当 cv.notify_all(); // 唤醒所有线程. 执行到这句wait就收到了信号就被唤醒开始干活，首先就是不断的尝试重新获取并加锁互斥量。
                      //若获取不到锁就卡在这里反复尝试加锁
                      //若获取到了锁才往下执行

    std::cout << "thread " << id << '\n';
}

void go()
{
    std::unique_lock <std::mutex> lck(mtx);
    ready = true; // 设置全局标志位为 true.
    cv.notify_all(); // 唤醒所有线程.
}

void test_try_lockwrongmutex();


int main()
{

//    std::thread threads[10];
//    // spawn 10 threads:

//    threads[0] = std::thread(do_print_id, 0);

//    std::this_thread::sleep_for(std::chrono::milliseconds(1000));

//    ready=true;
//    for (int i = 1; i < 10; ++i)
//        threads[i] = std::thread(do_print_id, i);

//    std::cout << "10 threads ready to race...\n";
////    go(); // go!

//  for (auto & th:threads)
//        th.join();

  test_try_lockwrongmutex();

    return 0;
}


/// 假设有锁以指针方式锁定调用
/// 原mutex被释放再次调用时会发生什么
/// 线程锁锁定时,释放线程锁,尝试解锁时会能溃

static std::mutex *__g_mutex=nullptr;
static std::mutex __g_mutex_nofree;
int _g_count=0;

void do_something()
{
  if (_g_count%2 != 0) {
    _g_count++;
//    std::this_thread::sleep_for(std::chrono::milliseconds(2000));
    free(__g_mutex);
//    __g_mutex=nullptr;
  }
  else{
    _g_count++;
    std::unique_lock<std::mutex> lck(*__g_mutex);
    std::cout<<"do_something:"<<_g_count<<std::endl;
    std::cout.flush();
    std::this_thread::sleep_for(std::chrono::milliseconds(5000));
  }
}

void test_try_lockwrongmutex()
{
  __g_mutex=new std::mutex;
  std::thread threads[3];
      for (int i = 0; i < 3; ++i)
      {
        threads[i] = std::thread(do_something);
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
      }


  for (auto & th:threads)
        th.join();

}

