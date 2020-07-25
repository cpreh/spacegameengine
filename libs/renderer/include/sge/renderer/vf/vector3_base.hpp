//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_RENDERER_VF_VECTOR3_BASE_HPP_INCLUDED
#define SGE_RENDERER_VF_VECTOR3_BASE_HPP_INCLUDED

#include <sge/renderer/vf/vector_base.hpp>


namespace sge
{
namespace renderer
{
namespace vf
{

template<
	typename Format
>
using vector3_base
=
sge::renderer::vf::vector_base<
	Format,
	3U
>;

}
}
}

#endif
