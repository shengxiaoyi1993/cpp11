#include <iostream>
#include <iostream>
#include <iomanip>
#include <climits>

/// 对于有符号 long long 整形，后缀用 "LL" 或者 "ll" 标识。例如，"10LL" 就表示有符号超长整数 10；
/// 对于无符号 long long 整形，后缀用 "ULL"、"ull"、"Ull" 或者 "uLL" 标识。例如，"10ULL" 就表示无符号超长整数 10；
///

using namespace std;

int main(int argc, char *argv[])
{

  cout <<"long long最大值：" << LLONG_MIN <<" "<< hex << LLONG_MIN <<"\n";
  cout << dec <<"long long最小值：" << LLONG_MAX << " " << hex << LLONG_MAX << "\n";
  cout << dec << "unsigned long long最大值：" << ULLONG_MAX << " " << hex << ULLONG_MAX;

  return 0;
}
