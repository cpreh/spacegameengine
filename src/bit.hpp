#ifndef SGE_BIT_HPP_INCLUDED
#define SGE_BIT_HPP_INCLUDED

#include <cstddef>
#include <climits>
#include <boost/array.hpp>

namespace sge
{

inline bool bit(const char c, const unsigned bit)
{
	return c & (1<<bit);
}
inline bool bit_a(const char c[], const unsigned bit)
{
	return c[bit/CHAR_BIT]&(1<<(bit%CHAR_BIT));
}
template<std::size_t sz> inline bool bit_a(const boost::array<char,sz>& c, const unsigned bit)
{
	return bit_a(c.data(),bit);
}

}

#endif
