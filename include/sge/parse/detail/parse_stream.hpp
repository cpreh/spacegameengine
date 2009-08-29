#ifndef SGE_PARSE_DETAIL_PARSE_STREAM_HPP_INCLUDED
#define SGE_PARSE_DETAIL_PARSE_STREAM_HPP_INCLUDED

#include <sge/istream.hpp>
#include <sge/string.hpp>

namespace sge
{
namespace parse
{
namespace detail
{
template<
	typename Result
>
bool parse_stream(
	istream &ifs,
	Result &result)
{
	string ret;

	{
		istream::char_type ch;
		while(ifs.get(ch))
			ret.push_back(ch);
	}
	
	typedef string::const_iterator iterator;

	iterator beg(
		ret.begin()
	);

	return parse_range(
		beg,
		static_cast<
			string const &
		>(
			ret
		).end(),
		result
	);
}
}
}
}

#endif
