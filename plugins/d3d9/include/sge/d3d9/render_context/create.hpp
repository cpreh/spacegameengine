//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_D3D9_RENDER_CONTEXT_CREATE_HPP_INCLUDED
#define SGE_D3D9_RENDER_CONTEXT_CREATE_HPP_INCLUDED

#include <sge/d3d9/render_context/parameters_fwd.hpp>
#include <sge/renderer/context/ffp_unique_ptr.hpp>


namespace sge
{
namespace d3d9
{
namespace render_context
{

sge::renderer::context::ffp_unique_ptr
create(
	sge::d3d9::render_context::parameters const &
);

}
}
}

#endif
