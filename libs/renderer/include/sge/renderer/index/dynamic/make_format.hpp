//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_RENDERER_INDEX_DYNAMIC_MAKE_FORMAT_HPP_INCLUDED
#define SGE_RENDERER_INDEX_DYNAMIC_MAKE_FORMAT_HPP_INCLUDED

#include <sge/renderer/detail/symbol.hpp>
#include <sge/renderer/index/detail/pp_formats.hpp>
#include <sge/renderer/index/dynamic/format_fwd.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/preprocessor/seq/for_each.hpp>
#include <fcppt/config/external_end.hpp>


namespace sge::renderer::index::dynamic
{

template<
	typename Format
>
SGE_RENDERER_DETAIL_SYMBOL
sge::renderer::index::dynamic::format
make_format();

}

#define SGE_RENDERER_INDEX_DYNAMIC_DETAIL_DECLARE_MAKE_FORMAT(\
	seq,\
	_,\
	cur_format\
)\
extern \
template \
SGE_RENDERER_DETAIL_SYMBOL \
sge::renderer::index::dynamic::format \
sge::renderer::index::dynamic::make_format<\
	cur_format \
>();

BOOST_PP_SEQ_FOR_EACH(
	SGE_RENDERER_INDEX_DYNAMIC_DETAIL_DECLARE_MAKE_FORMAT,
	_,
	SGE_RENDERER_INDEX_DETAIL_PP_FORMATS
)

#endif
