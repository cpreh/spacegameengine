#ifndef SGE_DETAIL_LEXICAL_CAST_IMPL_HPP_INCLUDED
#define SGE_DETAIL_LEXICAL_CAST_IMPL_HPP_INCLUDED

#include <sge/bad_lexical_cast.hpp>
#include <sge/type_traits/is_string.hpp>
#include <sge/mpl/value_type.hpp>
#include <boost/mpl/or.hpp>
#include <boost/mpl/eval_if.hpp>
#include <boost/static_assert.hpp>
#include <sstream>
#include <typeinfo>

template<
	typename Dest,
	typename Src
>
typename boost::disable_if<boost::is_same<Src,Dest>,Dest>::type
sge::lexical_cast(
	Src const &s)
{
	BOOST_STATIC_ASSERT((
		boost::mpl::or_<
			type_traits::is_string<
				Dest
			>,
			type_traits::is_string<
				Src
			>
		>::value
	));

	std::basic_stringstream<
		typename boost::mpl::eval_if<
			type_traits::is_string<
				Dest
			>,
			mpl::value_type<Dest>,
			mpl::value_type<Src>
		>::type
	> ss;

	Dest result;

	if (!(ss << s && ss >> result))
		throw bad_lexical_cast(typeid(Src),typeid(Dest));
	
	return result;
}

template<
	typename Src
>
Src
sge::lexical_cast(
	Src const &s)
{
	return s;
}

#endif
