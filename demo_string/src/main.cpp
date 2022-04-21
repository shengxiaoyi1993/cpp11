#include <iostream>
#include <string>
#include <vector>



using namespace std;


int main(int argc, char *argv[])
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




  return 0;
}
