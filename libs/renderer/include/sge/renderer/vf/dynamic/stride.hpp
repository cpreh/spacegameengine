//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_RENDERER_VF_DYNAMIC_STRIDE_HPP_INCLUDED
#define SGE_RENDERER_VF_DYNAMIC_STRIDE_HPP_INCLUDED

#include <sge/renderer/vf/vertex_size.hpp>
#include <fcppt/make_strong_typedef.hpp>
#include <fcppt/strong_typedef.hpp>


namespace sge
{
namespace renderer
{
namespace vf
{
namespace dynamic
{

FCPPT_MAKE_STRONG_TYPEDEF(
	sge::renderer::vf::vertex_size,
	stride
);

}
}
}
}

#endif
