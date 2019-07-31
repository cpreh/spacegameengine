//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/core/impl/export_function_instantiation.hpp>
#include <sge/renderer/impl/index/dynamic/format_enum_static.hpp>
#include <sge/renderer/index/format.hpp>
#include <sge/renderer/index/detail/pp_formats.hpp>
#include <sge/renderer/index/dynamic/format.hpp>
#include <sge/renderer/index/dynamic/make_format.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/preprocessor/seq/for_each.hpp>
#include <fcppt/config/external_end.hpp>


template<
	typename Format
>
sge::renderer::index::dynamic::format
sge::renderer::index::dynamic::make_format()
{
	return
		sge::renderer::impl::index::dynamic::format_enum_static<
			Format
		>::value;
}

#define SGE_RENDERER_INDEX_DYNAMIC_INSTANTIATE_MAKE_FORMAT(\
	seq,\
	_,\
	cur_format\
)\
template \
SGE_CORE_IMPL_EXPORT_FUNCTION_INSTANTIATION \
sge::renderer::index::dynamic::format \
sge::renderer::index::dynamic::make_format<\
	cur_format \
>();

BOOST_PP_SEQ_FOR_EACH(
	SGE_RENDERER_INDEX_DYNAMIC_INSTANTIATE_MAKE_FORMAT,
	_,
	SGE_RENDERER_INDEX_DETAIL_PP_FORMATS
)
