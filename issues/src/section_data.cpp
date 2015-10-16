#include <iostream>
#include <string>
#include <vector>
#include <utility>
#include <stdexcept>
#include <algorithm>

struct section_num
{
    std::string prefix;
    std::vector<int> num;
};

std::istream&
operator >> (std::istream& is, section_num& sn)
{
    sn.prefix.clear();
    sn.num.clear();
    ws(is);
    if (is.peek() == 'T')
    {
        is.get();
        if (is.peek() == 'R')
        {
            std::string w;
            is >> w;
            if (w == "R1")
                sn.prefix = "TR1";
            else if (w == "RDecimal")
                sn.prefix = "TRDecimal";
            else
                throw std::runtime_error("section_num format error");
            ws(is);
        }
        else
        {
            sn.num.push_back(100 + 'T' - 'A');
            if (is.peek() != '.')
                return is;
             is.get();
        }
    }
    while (true)
    {
        if (std::isdigit(is.peek()))
        {
            int n;
            is >> n;
            sn.num.push_back(n);
        }
        else
        {
            char c;
            is >> c;
            sn.num.push_back(100 + c - 'A');
        }
        if (is.peek() != '.')
            break;
        char dot;
        is >> dot;
    }
    return is;
}

std::ostream&
operator << (std::ostream& os, const section_num& sn)
{
    if (!sn.prefix.empty())
        os << sn.prefix << " ";
    if (sn.num.size() > 0)
    {
        if (sn.num.front() >= 100)
            os << char(sn.num.front() - 100 + 'A');
        else
            os << sn.num.front();
        for (unsigned i = 1; i < sn.num.size(); ++i)
        {
            os << '.';
            if (sn.num[i] >= 100)
                os << char(sn.num[i] - 100 + 'A');
            else
                os << sn.num[i];
        }
    }
    return os;
}

bool
operator<(const section_num& x, const section_num& y)
{
    if (x.prefix < y.prefix)
        return true;
    else if (y.prefix < x.prefix)
        return false;
    return x.num < y.num;
}

bool
operator==(const section_num& x, const section_num& y)
{
    if (x.prefix != y.prefix)
        return false;
    return x.num == y.num;
}

bool
operator!=(const section_num& x, const section_num& y)
{
    return !(x == y);
}

typedef std::string section_tag;

struct sort_first
{
    template <class T, class U>
    bool operator()(const T& x, const U& y)
    {
        return x.first < y.first;
    }
};

std::string
replace_all(std::string s, const std::string& old, const std::string& nw)
{
    typedef std::string::size_type size_type;
    size_type x = s.size() - 1;
    while (true)
    {
        size_type i = s.rfind(old, x);
        if (i == std::string::npos)
            break;
        s.replace(i, old.size(), nw);
        if (i == 0)
            break;
        x = i - 1;
    }
    return s;
}

int main ()
{
    std::vector<std::pair<section_num, section_tag> > v;
    while (std::cin)
    {
        section_tag t;
        std::cin >> t;
        if (std::cin.fail())
            break;
        section_num n;
        std::cin >> n;
        if (std::cin.fail())
            throw std::runtime_error("incomplete tag / num pair");
        t = replace_all(t, "&", "&amp;");
        t = replace_all(t, "<", "&lt;");
        t = replace_all(t, ">", "&gt;");
        t = '[' + t + ']';
        v.push_back(std::make_pair(n, t));
    }
    std::sort(v.begin(), v.end(), sort_first());
    for (std::vector<std::pair<section_num, section_tag> >::const_iterator i = v.begin(), e = v.end(); i != e; ++i)
    {
        const int indent = 4*(i->first.num.size()-1);
        for (int k = 0; k < indent; ++k)
            std::cout << ' ';
        std::cout << i->first << ' ' << i->second << '\n';
    }
}
