#include <iostream>
#include <mutex>



/// 获取明天的午夜时间
std::chrono::time_point<std::chrono::system_clock> midnight();
/// 将时刻转换成字符串
void transformTimepointToString();

/// 测试系统时钟于稳定时钟的关系
void testSteadyClock();

/// 将时刻转换成字符串 ns精度
void getDate(long long time);

/// 转换以ns/ms/s为精度的字符串 (时间点/时间段)
/// 转换成

int main(int argc, char *argv[])
{


  {
    // 获取当前时间
     std::chrono::system_clock::time_point now = std::chrono::system_clock::now();
     // 距离1970-01-01 00:00:00的纳秒数
     std::chrono::nanoseconds d = now.time_since_epoch();
     std::cout << "current nanoseconds:" << d.count() << std::endl <<  "currnet date time:  " ;
     getDate(d.count()) ;
  }


//  transformTimepointToString();

  return 0;
}


void getDate(long long time) {
    int seconds = time / 1000000000 + 8 * 3600;// time zone +8
    int days = seconds / 86400;
    int year = 1970 + (int) (days / 1461) * 4; // recycled in 4 years = 1461 days
    int month = 0;
    int day = days % 1461;
    day = day > 730 ? day - 1 : day;
    year += (int) (day / 365);
    day = day % 365;
    int monthday[]{0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334, 365};
    for (int i = 0; i < 13; i++) {
        if (day < monthday[i + 1]) {
            month = i + 1;
            day = day - monthday[i] + 1;
            break;
        }
    }
    int sec = seconds % 86400;
    int hour = (int) (sec / 3600);
    int minute = (int) (sec % 3600 / 60);
    int second = sec % 60;
    int nanoseconds = time % 1000000000;
    int millisecond = nanoseconds / 1000;

    std::cout << year << "/" << month << "/" << day << " " << hour << ":"
         << minute << ":" << second << "." << millisecond << std::endl;
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

#define ptm_output_para(X) \
  std::cout<<"X:"<<ptm->X<<std::endl;

  ptm_output_para(tm_sec);

#undef ptm_output_para



  /// 将天数加1,其他的置为0
  ++ptm->tm_mday; ptm->tm_hour=0; ptm->tm_min=0; ptm->tm_sec=0;
  /// 重新转换成time_point
  return system_clock::from_time_t (mktime(ptm));
}


/// chrone中的模块
/// steady_clock 开机到现在的时间
/// system_clock 系统时钟
/// - time_point 可以基于以上两种时钟
