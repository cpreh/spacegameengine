#ifndef SGE_LEXICAL_CAST_HPP_INCLUDED
#define SGE_LEXICAL_CAST_HPP_INCLUDED

#include <boost/utility/enable_if.hpp>
#include <boost/type_traits/is_same.hpp>

namespace sge
{
template<
	typename Dest,
	typename Src>
typename boost::disable_if<boost::is_same<Src,Dest>,Dest>::type
lexical_cast(
	Src const &);

template<
	typename Src>
Src
lexical_cast(
	Src const &);
}

#include <sge/detail/lexical_cast_impl.hpp>

#endif
