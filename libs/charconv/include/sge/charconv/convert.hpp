//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_CHARCONV_CONVERT_HPP_INCLUDED
#define SGE_CHARCONV_CONVERT_HPP_INCLUDED

#include <sge/charconv/encoding_fwd.hpp>
#include <sge/charconv/string_type.hpp>
#include <sge/charconv/detail/pp_encodings.hpp>
#include <sge/charconv/detail/symbol.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/preprocessor/seq/elem.hpp>
#include <boost/preprocessor/seq/for_each_product.hpp>
#include <fcppt/config/external_end.hpp>


namespace sge::charconv
{

template<
	sge::charconv::encoding DestEncoding,
	sge::charconv::encoding SourceEncoding
>
SGE_CHARCONV_DETAIL_SYMBOL
sge::charconv::string_type<
	DestEncoding
>
convert(
	sge::charconv::string_type<
		SourceEncoding
	> const &
);

}

#define SGE_CHARCONV_DETAIL_DECLARE_CONVERT(\
	r,\
	param\
)\
extern \
template \
SGE_CHARCONV_DETAIL_SYMBOL \
sge::charconv::string_type< \
	BOOST_PP_SEQ_ELEM(0, param) \
> \
sge::charconv::convert<\
	BOOST_PP_SEQ_ELEM(0, param),\
	BOOST_PP_SEQ_ELEM(1, param)\
>( \
	sge::charconv::string_type< \
		BOOST_PP_SEQ_ELEM(1, param) \
	> const & \
);

BOOST_PP_SEQ_FOR_EACH_PRODUCT(
	SGE_CHARCONV_DETAIL_DECLARE_CONVERT,
	(SGE_CHARCONV_DETAIL_PP_ENCODINGS)(SGE_CHARCONV_DETAIL_PP_ENCODINGS)
)

#endif
