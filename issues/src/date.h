// I, Howard Hinnant, hereby place this code in the public domain.
// Since tweaked by Alisdair Meredith, also in the public domain.

#ifndef DATE_H
#define DATE_H

#include <exception>
#include <istream>
#include <ostream>
#include <locale>
#include <ctime>

namespace gregorian
{

struct day;
struct date;

namespace detail
{

struct spec {
    spec() noexcept : id_{id_next++} {}

    bool operator == (const spec& y) const noexcept {return id_ == y.id_;}
    bool operator != (const spec& y) const noexcept {return id_ != y.id_;}

private:
    unsigned id_;
    static unsigned id_next;

    friend class gregorian::day;
};

}  // detail

extern const detail::spec last;
extern const detail::spec first;

struct bad_date : std::exception {
   virtual const char* what() const  noexcept {return "bad_date";}
};


struct week_day
{
   constexpr week_day(int d)
      : d_{(d < 0  or  d > 6) ? throw bad_date{} : d}
      {
   }

private:
    int d_;

    friend class ::gregorian::date;
    friend day operator*(detail::spec s, week_day wd);
    friend day operator*(int n, week_day wd);
};


struct day {
   constexpr day(int d)
      : d_{(d < 1  or  d > 31) ? throw bad_date{} : (unsigned char)d}
      {
   }

   day(detail::spec s) noexcept : d_{(unsigned char)s.id_} {}

private:
    unsigned char d_;

    friend class gregorian::date;
    friend day operator*(detail::spec s, week_day wd);
    friend day operator*(int n, week_day wd);
};


struct month {
    constexpr month(int m) noexcept : value{m} {}
    int value;
};


struct year {
    constexpr year(int y) noexcept : value{y} {}
    int value;
};


static constexpr week_day sun{0};
static constexpr week_day mon{1};
static constexpr week_day tue{2};
static constexpr week_day wed{3};
static constexpr week_day thu{4};
static constexpr week_day fri{5};
static constexpr week_day sat{6};

static constexpr month jan{1};
static constexpr month feb{2};
static constexpr month mar{3};
static constexpr month apr{4};
static constexpr month may{5};
static constexpr month jun{6};
static constexpr month jul{7};
static constexpr month aug{8};
static constexpr month sep{9};
static constexpr month oct{10};
static constexpr month nov{11};
static constexpr month dec{12};

namespace detail
{

struct day_month_spec {
    constexpr day_month_spec(day d, month m);

private:
    day   d_;
    month m_;

    friend class gregorian::date;
};

inline constexpr
day_month_spec::day_month_spec(day d, month m)
   : d_{d}
   , m_{m}
   {
}

struct month_year_spec
{
    constexpr month_year_spec(month m, year y);

private:
    month m_;
    year  y_;

    friend class gregorian::date;
};

inline constexpr
month_year_spec::month_year_spec(month m, year y)
   : m_{m}
   , y_{y}
   {
}

}  // detail

date operator+(const date&, month);
date operator+(const date&, year);

struct date {
    date();
    date(detail::day_month_spec dm, gregorian::year y);
    date(gregorian::day d, detail::month_year_spec my);

    constexpr int day()   const noexcept {return day_ & 0x1F;}
    constexpr int month() const noexcept {return month_ & 0x0F;}
    constexpr int year()  const noexcept {return year_;}
    constexpr int day_of_week() const noexcept  {return static_cast<int>((jdate_+3) % 7);}
    bool is_leap() const noexcept;

    date& operator+=(int d);
    date& operator++() {return *this += 1;}
    date  operator++(int) {date tmp(*this); *this += 1; return tmp;}
    date& operator-=(int d) {return *this += -d;}
    date& operator--() {return *this -= 1;}
    date  operator--(int) {date tmp(*this); *this -= 1; return tmp;}
    friend date operator+(const date& x, int y) {date r(x); r += y; return r;}
    friend date operator+(int x, const date& y) {return y + x;}
    friend date operator-(const date& x, int y) {date r(x); r += -y; return r;}

    date& operator+=(gregorian::month m) {*this = *this + m; return *this;}
    date& operator-=(gregorian::month m) {return *this += gregorian::month(-m.value);}
    friend date operator+(gregorian::month m, const date& y) {return y + m;}
    friend date operator-(const date& x, gregorian::month m) {date r(x); r -= m; return r;}

    date& operator+=(gregorian::year y) {*this = *this + y; return *this;}
    date& operator-=(gregorian::year y) {return *this += gregorian::year(-y.value);}
    friend date operator+(gregorian::year y, const date& x) {return x + y;}
    friend date operator-(const date& x, gregorian::year y) {date r(x); r -= y; return r;}

    friend constexpr long operator- (const date& x, const date& y) noexcept {return (long)(x.jdate_ - y.jdate_);}
    friend constexpr bool operator==(const date& x, const date& y) noexcept {return x.jdate_ == y.jdate_;}
    friend constexpr bool operator!=(const date& x, const date& y) noexcept {return x.jdate_ != y.jdate_;}
    friend constexpr bool operator< (const date& x, const date& y) noexcept {return x.jdate_ <  y.jdate_;}
    friend constexpr bool operator<=(const date& x, const date& y) noexcept {return x.jdate_ <= y.jdate_;}
    friend constexpr bool operator> (const date& x, const date& y) noexcept {return x.jdate_ >  y.jdate_;}
    friend constexpr bool operator>=(const date& x, const date& y) noexcept {return x.jdate_ >= y.jdate_;}

private:

   constexpr date(int y, int m, int d)
      : jdate_{}
      , year_{(unsigned short)y}
      , month_{(unsigned char)m}
      , day_{(unsigned char)d}
      {
   }

   void init();
   void fix_from_ymd();
   void fix_from_jdate();
   void decode(int& dow, int& n) const noexcept;
   void encode(int dow, int n) noexcept;

   friend date operator+(const date&, gregorian::month);
   friend date operator+(const date&, gregorian::year);

private:
   unsigned long jdate_;
   unsigned short year_;
   unsigned char month_;
   unsigned char day_;

//   static const unsigned char lastDay_s[12];
};

//constexpr unsigned char date::lastDay_s[12] { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

auto operator*(detail::spec s, week_day wd) -> day;
auto operator*(int n, week_day wd) -> day;


inline constexpr
auto operator/(day d, month m) -> detail::day_month_spec {
   return detail::day_month_spec{d, m};
}

inline constexpr
auto operator/(month m, day d) -> detail::day_month_spec {
   return detail::day_month_spec{d, m};
}

inline constexpr
auto operator/(year y, month m) -> detail::month_year_spec {
   return detail::month_year_spec{m, y};
}

inline
auto operator/(detail::day_month_spec dm, year y) -> date {
   return date{dm, y};
}

inline
auto operator/(detail::month_year_spec my, day d) -> date {
   return date{d, my};
}


namespace detail
{

inline
auto operator/(spec d, int m) -> detail::day_month_spec {
   return day{d} / month{m};
}

inline
auto operator/(int m, spec d) -> detail::day_month_spec {
   return day{d} / month{m};
}

inline
auto operator/(detail::day_month_spec dm, int y) -> date {
   return date{dm, year{y}};
}

inline
auto operator/(detail::month_year_spec my, int d) -> date {
   return date{day{d}, my};
}

}  // detail

template<class charT, class traits>
auto operator >>(std::basic_istream<charT,traits> & is, date & item) -> std::basic_istream<charT,traits> & {
   typename std::basic_istream<charT,traits>::sentry ok(is);
   if (ok) {
      std::ios_base::iostate err = std::ios_base::goodbit;
      try {
         std::time_get<charT> const & tg = std::use_facet<std::time_get<charT> >(is.getloc());
         std::tm t;
         tg.get_date(is, 0, is, err, &t);
         if (!(err & std::ios_base::failbit)) {
            item = date(month(t.tm_mon+1) / day(t.tm_mday) / year(t.tm_year+1900));
         }
      }
      catch (...) {
         err |= std::ios_base::badbit | std::ios_base::failbit;
      }
      is.setstate(err);
   }
   return is;
}

template<class charT, class traits>
auto operator <<(std::basic_ostream<charT, traits> & os, date const & item) -> std::basic_ostream<charT, traits> & {
   typename std::basic_ostream<charT, traits>::sentry ok{os};
   if (ok) {
      bool failed;
      try {
         std::time_put<charT> const & tp = std::use_facet<std::time_put<charT> >(os.getloc());
         std::tm t;
         t.tm_mday = item.day();
         t.tm_mon = item.month() - 1;
         t.tm_year = item.year() - 1900;
         t.tm_wday = item.day_of_week();
         charT pattern[2] = {'%', 'x'};
         failed = tp.put(os, os, os.fill(), &t, pattern, pattern+2).failed();
      }
      catch (...) {
         failed = true;
      }

      if (failed) {
         os.setstate(std::ios_base::failbit | std::ios_base::badbit);
      }
   }
   return os;
}

}  // gregorian

#endif  // DATE_H
