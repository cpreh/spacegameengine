//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_RENDERER_VF_IS_VERTEX_HPP_INCLUDED
#define SGE_RENDERER_VF_IS_VERTEX_HPP_INCLUDED

#include <sge/renderer/vf/vertex_fwd.hpp>
#include <fcppt/config/external_begin.hpp>
#include <type_traits>
#include <fcppt/config/external_end.hpp>


namespace sge::renderer::vf
{

template<
	typename Type
>
struct is_vertex
:
std::false_type
{
};

template<
	typename Part
>
struct is_vertex<
	sge::renderer::vf::vertex<
		Part
	>
>
:
std::true_type
{
};

}

#endif
