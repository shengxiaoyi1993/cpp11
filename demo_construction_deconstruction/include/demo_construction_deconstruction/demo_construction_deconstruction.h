#ifndef demo_construction_deconstruction_h
#define demo_construction_deconstruction_h

#include <iostream>

class BaseA{
public:
  BaseA(){std::cout<<__func__<<std::endl;}
  ~BaseA(){std::cout<<__func__<<std::endl;}
};

class BaseB{
public:
  BaseB(){std::cout<<__func__<<std::endl;}
  ~BaseB(){std::cout<<__func__<<std::endl;}
};

class BaseC{
public:

  BaseC(){std::cout<<__func__<<std::endl;}
  ~BaseC(){std::cout<<__func__<<std::endl;}
};


///
class BanDefault{

public:
  int __val;

public:
  BanDefault()=delete;
  BanDefault (const BanDefault & a) =delete;
  ~BanDefault()=delete;
  void operator = (const BanDefault & a) =delete;
  BanDefault* operator & () =delete;
  const BanDefault* operator &() const =delete;
};

class AllDefault{

};

class AddMove{
public:
  AddMove()=default;
  AddMove(AddMove && v){}
   AddMove(const AddMove &v){}
   AddMove& operator=(const AddMove&){
     return *this;
   }
   AddMove& operator=(AddMove&&){
     return *this;
   }


};


/// ? 禁用了移动构造函数,默认构造函数也用不了了
class BanMove
{
public:
  BanMove()=default;
  BanMove(BanMove && v)=delete;


};




class CTest0
{
public:
  CTest0(){std::cout<<__func__<<std::endl;}
  ~CTest0(){std::cout<<__func__<<std::endl;}

private:
  BaseA __ba;
  BaseB __bb;
  BaseC __bc;
};


class CTest1
{
public:
  CTest1():
    __bc(),
    __bb()
  {std::cout<<__func__<<std::endl;}
  ~CTest1(){std::cout<<__func__<<std::endl;}

public:
  BaseB __bb;


private:
  BaseA __ba;
  BaseC __bc;
};






template< typename T>
inline
void printClassTraits(const T &)
{
  std::cout << "is_move_constructible: "
            << std::is_move_constructible<T>::value
            << std::endl;
  std::cout << "is_copy_constructible: "
            << std::is_copy_constructible<T>::value
            << std::endl;
  std::cout << "is_copy_assignable: "
            << std::is_copy_assignable<T>::value
            << std::endl;
  std::cout << "is_move_assignable: "
            << std::is_move_assignable<T>::value
            << std::endl;
}





#endif
