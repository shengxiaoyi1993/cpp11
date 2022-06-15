#include <iostream>
#include <demo_construction_deconstruction/demo_construction_deconstruction.h>

/// 结论:
/// 类中的成员函数总是以声明顺序进行初始化;逆向顺序进行析构
/// 类的拷贝构造函数与拷贝赋值的函数参数是


int main(int argc, char const *argv[])
{
  CTest0 ct0_0;
  CTest1 ct1_0;

  AllDefault adf_0;

  std::cout<<"CTest0:"<<std::endl;
  printClassTraits<CTest0>(ct0_0);
  std::cout<<"CTest1:"<<std::endl;
  printClassTraits<CTest1>(ct1_0);
  std::cout<<"AllDefault:"<<std::endl;
  printClassTraits<AllDefault>(adf_0);

//  BanDefault bdf;

  AllDefault adf_1=std::move(adf_0);
  AllDefault adf_2(std::move(adf_0));

  CTest0 ct0_1=std::move(ct0_0);
  CTest0 ct0_2(std::move(ct0_1));

  BanMove bm_0;

  std::cout<<"BanMove:"<<std::endl;
  printClassTraits<BanMove>(bm_0);

  AddMove am_0;
  AddMove am_1=std::move(am_0);
  AddMove am_2;
  AddMove am_3 = (am_2=std::move(am_1));

  std::cout<<"AddMove:"<<std::endl;
  printClassTraits<AddMove>(am_0);

//  BanMove ct0_1=std::move(bm_0);
//  BanMove ct0_2(std::move(bm_0));

}

