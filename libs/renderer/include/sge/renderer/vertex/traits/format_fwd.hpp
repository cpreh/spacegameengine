//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_RENDERER_VERTEX_TRAITS_FORMAT_FWD_HPP_INCLUDED
#define SGE_RENDERER_VERTEX_TRAITS_FORMAT_FWD_HPP_INCLUDED

#include <sge/image/traits/pixel/format_tpl_fwd.hpp>
#include <sge/renderer/vertex/tag.hpp>
#include <sge/renderer/vf/dynamic/const_part_ref.hpp>


namespace sge::image::traits::pixel
{

template<>
struct format_tpl<
	sge::renderer::vertex::tag
>
{
	using
	type
	=
	sge::renderer::vf::dynamic::const_part_ref;
};

}

#endif
