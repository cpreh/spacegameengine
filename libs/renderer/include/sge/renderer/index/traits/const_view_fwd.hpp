//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_RENDERER_INDEX_TRAITS_CONST_VIEW_FWD_HPP_INCLUDED
#define SGE_RENDERER_INDEX_TRAITS_CONST_VIEW_FWD_HPP_INCLUDED

#include <sge/renderer/buffer/traits/const_view_tpl_fwd.hpp>
#include <sge/renderer/index/tag.hpp>
#include <sge/renderer/index/dynamic/const_view_fwd.hpp>


namespace sge::renderer::buffer::traits
{

template<>
struct const_view_tpl<
	sge::renderer::index::tag
>
{
	using
	type
	=
	sge::renderer::index::dynamic::const_view;
};

}

#endif
