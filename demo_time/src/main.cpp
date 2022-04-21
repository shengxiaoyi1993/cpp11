#include <iostream>
#include <mutex>




std::chrono::time_point<std::chrono::system_clock> midnight();
void transformTimepointToString();
void testSteadyClock();

int main(int argc, char *argv[])
{
  testSteadyClock();

  time_t tm;
  std::time(&tm);

  std::cout<<"tm:"<<tm<<std::endl;

  return 0;
}

void transformTimepointToString( )
{
  auto tp=midnight();
  std::time_t tt= std::chrono::system_clock::to_time_t(tp);
  struct std::tm info;
  info = *std::localtime(&tt);
  char buffer[80];
  strftime(buffer, 80, "%Y-%m-%d %H:%M:%S", &info);
  printf("格式化的日期 & 时间 : |%s|\n", buffer);
}



void testSteadyClock()
{
  auto tp_now_steady=std::chrono::steady_clock::now();
  std::cout<<"tp_now_steady:"<<tp_now_steady.time_since_epoch().count()<<std::endl;

  auto tp_now_sys=std::chrono::system_clock::now();
  std::cout<<"tp_now_sys:"<<tp_now_sys.time_since_epoch().count()<<std::endl;

}


// gets time_point for next midnight:
std::chrono::time_point<std::chrono::system_clock> midnight() {
  using std::chrono::system_clock;

  /// 获取当前时间
  std::time_t tt = system_clock::to_time_t (system_clock::now());

  /// 转换格式
  struct std::tm * ptm = std::localtime(&tt);
  /// 将天数加1,其他的置为0
  ++ptm->tm_mday; ptm->tm_hour=0; ptm->tm_min=0; ptm->tm_sec=0;
  /// 重新转换成time_point
  return system_clock::from_time_t (mktime(ptm));
}


/// chrone中的模块
/// steady_clock 开机到现在的时间
/// system_clock 系统时钟
/// - time_point 可以基于以上两种时钟
