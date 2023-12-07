//#include <iostream>

//class ExceptionA
//{
//public:
//  ExceptionA(const std::string &v_error):
//    __error(v_error)
//  {
//  }
//  void print() const
//  {
//    std::cout<<"__error:"<<__error<<std::endl;
//  }
//private:
//  std::string __error;
//};

//int main(int argc, char *argv[])
//{

//  try {
//    throw ExceptionA("ExceptionA ...");
//  } catch (const ExceptionA & ex) {
//    ex.print();
//  }

//  return 0;
//}


#include<iostream>
#include<thread>
#include<exception>
#include<stdexcept>

/// 使用全局异常使主线程能够捕获
static std::exception_ptr globalExceptionPtr = nullptr;

void LaunchRocket()
{
  try
  {
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    throw std::runtime_error("Catch me in MAIN");
  }
  catch (...)
  {
    std::cout << "Thread exited with exception: LaunchRocket \n";
    //Set the global exception pointer in case of an exception
    globalExceptionPtr = std::current_exception();
  }
}

void rethrow()
{
  if (globalExceptionPtr)
  {
    try
    {
      std::rethrow_exception(globalExceptionPtr);
    }
    catch (const std::exception &ex)
    {
      std::cout << "Thread exited with exception: " << ex.what() << "\n";
    }
    catch(...){
      std::cout << "Thread exited with exception: other \n";

    }
  }
}


int main()
{

  std::thread t1(LaunchRocket);
  t1.join();

  /// 可以在任意线程中捕获
  std::thread t2(rethrow);
  t2.join();



//  if (globalExceptionPtr)
//  {
//    try
//    {
//      std::rethrow_exception(globalExceptionPtr);
//    }
//    catch (const std::exception &ex)
//    {
//      std::cout << "Thread exited with exception: " << ex.what() << "\n";
//    }
//    catch(...){
//      std::cout << "Thread exited with exception: other \n";

//    }
//  }

  return 0;
}
