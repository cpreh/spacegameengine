#ifndef SGE_BIN_IO_HPP_INCLUDED
#define SGE_BIN_IO_HPP_INCLUDED

#include <ostream>
#include <istream>
#include <string>

namespace sge
{
    template<class T, class Ch, class Traits> std::basic_ostream<Ch>& bin_write(std::basic_ostream<Ch,Traits>& s, const T& t)
	{
		return s.write(reinterpret_cast<const Ch*>(&t),sizeof(T) / sizeof(Ch));
	}
	template<class T, class Ch, class Traits> std::basic_istream<Ch>& bin_read(std::basic_istream<Ch,Traits>& s, T& t)
	{
		return s.read(reinterpret_cast<Ch*>(&t),sizeof(T) / sizeof(Ch));
	}
	template<class Ch, class Traits> std::basic_ostream<Ch,Traits>& bin_write(std::basic_ostream<Ch,Traits>& s, const std::basic_string<Ch,Traits>& t)
	{
		bin_write(s,t.size());
		for(typename std::basic_string<Ch,Traits>::const_iterator it = t.begin(); it != t.end(); ++it)
			bin_write(s,*it);
		return s;
	}
	template<class Ch, class Traits> std::basic_istream<Ch>& bin_read(std::basic_istream<Ch,Traits>& s, std::basic_string<Ch,Traits>& t)
	{
		typedef typename std::basic_string<Ch> strtype;
		typename strtype::size_type sz;
		bin_read(s,sz);
		t.resize(sz);
		for(typename strtype::iterator it = t.begin(); it != t.end(); ++it)
			bin_read(s,*it);
		return s;
	}
}

#endif
