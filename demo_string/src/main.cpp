#include <iostream>
#include <string>
#include <vector>
#include <map>

using namespace std;


void test_split();

/// 查找原始字符串中的一段字符,并替换为任意长度的字符串
void test_replace();
void case_map();
void case_print_map(const std::map<std::string ,std::string >& l_data);





int main(int argc, char *argv[])
{

  case_map();

//  test_replace();


  return 0;
}

void case_map()
{
  std::map<std::string,std::string> list_data;
  list_data["NODE_ID"]="1";
  std::cout<<list_data["NODE_ID"]<<std::endl;
  case_print_map(list_data);
}
void case_print_map(const std::map<std::string ,std::string >& l_data)
{
  /// [] 运算会再 索引不存在时创建一个索引
  //  std::cout<<l_data["NODE_ID"]<<std::endl;//error

  auto pos=l_data.find("NODE_ID");
  if (pos != l_data.end()) {
    std::cout<<pos->second<<std::endl;
  }
}



void test_replace()
{
  std::string longstring="rtsp://192.168.1.100:8557/h264";
  std::string to_replace="h264";
  std::string newstring="sub_stream_1";

  auto pos=longstring.find(to_replace);
  if (pos != std::string::npos) {
    longstring.erase(pos,to_replace.size());
    longstring.insert(pos,newstring);
    std::cout<<"result:"<<longstring<<std::endl;
  }
  else{
    std::cout<<"cannot find"<<std::endl;
  }

  /// find
  /// delete
  /// insert

}


void test_split()
{
  vector<string> l_str={
    "admin:123456",
    "admin:",
    ":",
    ":123456",
    "",
    "123345"
  };

  for (auto v_str:l_str) {
    cout<<"v_str:"<<v_str<<endl;

    size_t pos= v_str.find_first_of(":");

    string __user;
    string __password;

    if (pos!= string::npos) {
      ///截取
      __user=v_str.substr(0,pos);
      ///截取":"之后的字符串
      __password=v_str.substr(pos+1);
    }

    cout<<"__user:"<<__user<<endl;
    cout<<"__password:"<<__password<<endl<<endl;
  }

}

