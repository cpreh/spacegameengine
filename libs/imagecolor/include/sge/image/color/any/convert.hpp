//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_IMAGE_COLOR_ANY_CONVERT_HPP_INCLUDED
#define SGE_IMAGE_COLOR_ANY_CONVERT_HPP_INCLUDED

#include <sge/image/color/enable_if_has_format.hpp>
#include <sge/image/color/tag.hpp>
#include <sge/image/color/any/object_fwd.hpp>
#include <sge/image/color/detail/pp_formats.hpp>
#include <sge/image/color/detail/symbol.hpp>
#include <sge/image/pixel/declare_convert.hpp>
#include <sge/image/pixel/mizuiro_type.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/seq/for_each.hpp>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace image
{
namespace color
{
namespace any
{

template<
	typename Format
>
SGE_IMAGE_COLOR_DETAIL_SYMBOL
sge::image::color::enable_if_has_format<
	Format,
	sge::image::pixel::mizuiro_type<
		Format
	>
>
convert(
	sge::image::color::any::object const &
);

}
}
}
}

#define SGE_IMAGE_COLOR_ANY_DETAIL_DECLARE_CONVERT(\
	seq,\
	_,\
	format_arg\
)\
extern \
template \
SGE_IMAGE_COLOR_DETAIL_SYMBOL \
sge::image::color::enable_if_has_format<\
	sge::image::color:: BOOST_PP_CAT(format_arg, _format),\
	sge::image::pixel::mizuiro_type<\
		sge::image::color:: BOOST_PP_CAT(format_arg, _format)\
	> \
> \
sge::image::color::any::convert<\
	sge::image::color:: BOOST_PP_CAT(format_arg, _format)\
>(\
	sge::image::color::any::object const &\
) \
; \
SGE_IMAGE_PIXEL_DECLARE_CONVERT(\
	sge::image::color::tag,\
	sge::image::color:: BOOST_PP_CAT(format_arg,_format)\
) \
;

BOOST_PP_SEQ_FOR_EACH(
	SGE_IMAGE_COLOR_ANY_DETAIL_DECLARE_CONVERT,
	_,
	SGE_IMAGE_COLOR_DETAIL_PP_FORMATS
)

#endif
