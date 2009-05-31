#ifndef SGE_ALGORITHM_JOIN_STRINGS_HPP_INCLUDED
#define SGE_ALGORITHM_JOIN_STRINGS_HPP_INCLUDED

#include <sge/string.hpp>
#include <boost/foreach.hpp>

namespace sge
{
namespace algorithm
{
template<typename Range>
string const join_strings(
	Range const &r,
	string const &delim)
{
	string s;
	BOOST_FOREACH(string const &n,r)
		s += n+delim;
	s.erase(s.length()-delim.length());
	return s;
}
}
}

#endif
