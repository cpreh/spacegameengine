//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/core/impl/export_function_instantiation.hpp>
#include <sge/image/color/enable_if_has_format.hpp>
#include <sge/image/color/format.hpp>
#include <sge/image/color/format_from_static.hpp>
#include <sge/image/color/tag.hpp>
#include <sge/image/color/detail/pp_formats.hpp>
#include <sge/image/color/impl/traits/format_map.hpp>
#include <sge/image/color/traits/format_fwd.hpp>
#include <sge/image/impl/format_from_static_impl.hpp>
#include <sge/image/impl/instantiate_format_from_static.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/seq/for_each.hpp>
#include <fcppt/config/external_end.hpp>


template<
	typename Format
>
sge::image::color::enable_if_has_format<
	Format,
	sge::image::color::format
>
sge::image::color::format_from_static()
{
	return
		sge::image::format_from_static<
			sge::image::color::tag,
			Format
		>();
}

#define SGE_INSTANTIATE_COLOR_FORMAT_FROM_STATIC(\
	seq,\
	_,\
	format_arg\
)\
template \
SGE_CORE_IMPL_EXPORT_FUNCTION_INSTANTIATION \
sge::image::color::enable_if_has_format< \
	sge::image::color:: BOOST_PP_CAT(format_arg,_format),\
	sge::image::color::format \
> \
sge::image::color::format_from_static<\
	sge::image::color:: BOOST_PP_CAT(format_arg,_format)\
>() \
; \
SGE_IMAGE_IMPL_INSTANTIATE_FORMAT_FROM_STATIC(\
	sge::image::color::tag,\
	sge::image::color:: BOOST_PP_CAT(format_arg,_format)\
) \
;

BOOST_PP_SEQ_FOR_EACH(
	SGE_INSTANTIATE_COLOR_FORMAT_FROM_STATIC,
	_,
	SGE_IMAGE_COLOR_DETAIL_PP_FORMATS
)
