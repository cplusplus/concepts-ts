// I, Howard Hinnant, hereby place this code in the public domain.

#include "date.h"
#include <time.h>

namespace gregorian
{

namespace detail
{

unsigned spec::id_next = 0;

}  // detail


//static const unsigned char date::lastDay_s[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
static constexpr unsigned char date_lastDay_s[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

const detail::spec last;
const detail::spec first;


date::date() {
    time_t systime;
    time(&systime);
    struct tm* now = std::localtime(&systime);
    year_ = (unsigned short)(now->tm_year+1900);
    month_ = (unsigned char)(now->tm_mon+1);
    day_ = (unsigned char)(now->tm_mday);
    fix_from_ymd();
}

date::date(detail::day_month_spec dm, gregorian::year y)
   :  year_{(unsigned short)y.value}
   ,  month_{(unsigned char)dm.m_.value}
   ,  day_{dm.d_.d_}
   {
   init();
}

date::date(gregorian::day d, detail::month_year_spec my)
   :  year_{(unsigned short)my.y_.value}
   ,  month_{(unsigned char)my.m_.value}
   ,  day_{d.d_}
   {
   init();
}


void date::init() {
   if (day_ & 0xE0) {
      int dow = ((day_ & 0xE0) >> 5) - 1;
      int n = day_ & 0x1F;
      if (n == 0) {
         n = 6;
      }
      day_ = 0;
      encode(dow, n);
   }
   else if (day_ == 0) {
      encode(-1, 6);
   }
   fix_from_ymd();
}


void date::decode(int& dow, int& n) const noexcept {
   if (day_ & 0xE0) {
      dow = ((day_ & 0xE0) >> 5) - 1;
   }
   else {
      dow = -1;
   }
   n = month_ >> 4;
}


void date::encode(int dow, int n) noexcept {
   day_ &= 0x1F;
   month_ &= 0x0F;
   if (dow >= 0) {
      day_ |= (unsigned char)((dow + 1) << 5);
   }
   month_ |= (unsigned char)(n << 4);
}

// This could be turned into a constexpr free-function taking 'year' by value as its argument.
// However, there would be no advantage in the application we are currently working on.
auto date::is_leap() const noexcept -> bool {
   if (year_ > 1582) {
      if (year_ % 400 == 0) {
         return true;
      }
      if (year_ % 100 == 0) {
         return false;
      }
   }
   return year_ % 4 == 0;
}

void date::fix_from_ymd() {
   int dow, n;
   decode(dow, n);
   int d = day();
   int m = month();
   int y = year();
   if (0 <= dow && dow <= 6) {
      if (n == 0 || n >  6) {
         throw bad_date{};
      }
      date tmp1 = gregorian::day(1) / m / y;
      date tmp2 = last / m / y;
      int wd = tmp1.day_of_week();
      int delta{0};
      if (dow != wd) {
         if (dow < wd) {
            delta += 7 - (wd - dow);
         }
         else {
            delta += dow - wd;
         }
      }
      delta += (n-1)*7;
      if (n == 6  and  delta >= tmp2.day()) {
         delta -= 7 * ((delta - tmp2.day()) / 7 + 1);
      }
      tmp1 += delta;
      if (tmp1.month() != m) {
         throw bad_date{};
      }
      *this = tmp1;
      encode(dow, n);
      return;
   }

   if (dow != -1) {
      throw bad_date{};
   }
   if (n != 0  and  n != 6) {
      throw bad_date();
   }
   if ((d == 0  and  n == 0)  or  m == 0  or  m > 12) {
      throw bad_date{};
   }

   if (n == 6) {
      d = 0;
   }

   unsigned long jdate = 0;
   bool leap = is_leap();
   if (leap  and  m == 2) {
      if (d > 29) {
      throw bad_date{};
      }
      if (n == 6) {
      d = 29;
      }
   }
   else {
      if (d > date_lastDay_s[m-1]) {
         throw bad_date{};
      }
      if (n == 6) {
         d = date_lastDay_s[m-1];
      }
   }

   if (y == 1582  and  m == 10  and  d >= 5  and  d <= 14) {
      throw bad_date{};
   }

   if (y > 0) {
      jdate = 365U * y + 1;   // Jan 1, 0 == 1 && y 0 is leap y
      --y;
      jdate += y / 4;
      if (y >= 1700) {
         jdate += -(y-1600) / 100 + (y-1600) / 400;
      }
      ++y;
   }

   for (int i = 0; i < m-1; ++i) {
      jdate += date_lastDay_s[i];
   }
   if (leap  and  m > 2) {
      ++jdate;
   }
   jdate += d;
   //  If date >= 10/15/1582 then subtract 10
   if (jdate >= 578114) {
      jdate -= 10;
   }

//  if (y >= 1582) {
//      if (y == 1582) {
//          if (m >= 10) {
//              if (m == 10) {
//                  if (d >= 15) {
//                      jdate -= 10;
//                  }
//              }
//              else {      // m > 10
//                  jdate -= 10;
//              }
//          }
//      }
//      else {      // y > 1582
//          jdate -= 10;
//      }
//  }

   if (jdate <= 0) {
      throw bad_date{};
   }

   jdate_ = jdate;
   year_ = (unsigned short)y;
   month_ = (unsigned char)m;
   day_ = (unsigned char)d;
   encode(dow, n);
}


void date::fix_from_jdate() {
   if (jdate_ <= 0) {
      throw bad_date{};
   }

   int dow, n;
   decode(dow, n);
   year_ = static_cast<unsigned short>(jdate_ / 365.2475);
   date lower = gregorian::day(1) / 1 / year_;
   date upper = gregorian::day(31) / 12 / year_;
   for(;;) {
      if (lower.jdate_ > jdate_) {
         --year_;
      }
      else if (upper.jdate_ < jdate_) {
         ++year_;
      }
      else {
      break;
         }
      lower = gregorian::day(1) / 1 / year_;
      upper = gregorian::day(31) / 12 / year_;
   }

   month_ = static_cast<unsigned char>((jdate_ - lower.jdate_) / 30 + 1);
   if (month_ > 12) {
      month_ = 12;
   }

   for(;;) {
      lower = gregorian::day(1) / month_ / year_;
      upper = gregorian::last / month_ / year_;
      if (lower.jdate_ > jdate_) {
         --month_;
      }
      else if (upper.jdate_ < jdate_) {
         ++month_;
      }
      else {
         break;
      }
   }

   day_ = static_cast<unsigned char>(jdate_ - lower.jdate_ + 1);
   if (year_ == 1582  and  month_ == 10  and  day_ >= 5) {
      day_ += 10;
   }
}


auto date::operator+=(int d) -> date & {
   jdate_ += d;
   fix_from_jdate();
   return *this;
}

}  // gregorian

// gcc will not recognise 'noexcept' specifier as matching the header
auto gregorian::operator*(detail::spec s, week_day wd) -> day {
   day d{1};
   d.d_ = (unsigned char)((wd.d_+1) << 5);
   if (s == first) {
      d.d_ |= 1;
   }
   return d;
}


auto gregorian::operator*(int n, week_day wd) -> day {
   day d{1};
   if (n < 1  or  n > 5) {
      throw bad_date{};
   }
   d.d_ = (unsigned char)(((wd.d_+1) << 5) | n);
   return d;
}


auto gregorian::operator+(const date& dt, month mnth) -> date {
   int dow, n;
   dt.decode(dow, n);
   int y = dt.year();
   int m = dt.month();
   int d = dt.day();
   int new_month = m - 1 + mnth.value;
   if (new_month < 0) {
      int delta = ((-new_month - 1) / 12 + 1) * 12;
      y -= delta / 12;
      new_month += delta;
   }
   else if (new_month > 11) {
      int delta = ((new_month - 12) / 12 + 1) * 12;
      y += delta / 12;
      new_month -= delta;
   }
   m = new_month + 1;
   date result{y, m, d};
   result.encode(dow, n);
   result.fix_from_ymd();
   return result;
}


auto gregorian::operator+(date const & dt, year yr) -> date {
   int dow, n;
   dt.decode(dow, n);
   int y = dt.year() + yr.value;
   int m = dt.month();
   int d = dt.day();
   date result{y, m, d};
   result.encode(dow, n);
   result.fix_from_ymd();
   return result;
}
