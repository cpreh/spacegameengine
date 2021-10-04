//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_RENDERER_INDEX_FORMAT_IS_32_HPP_INCLUDED
#define SGE_RENDERER_INDEX_FORMAT_IS_32_HPP_INCLUDED

#include <sge/renderer/index/i32.hpp>
#include <fcppt/config/external_begin.hpp>
#include <type_traits>
#include <fcppt/config/external_end.hpp>


namespace sge::renderer::index
{

template<
	typename Format
>
using format_is_32
=
std::is_same<
	typename Format::index_type,
	sge::renderer::index::i32
>;

}

#endif
