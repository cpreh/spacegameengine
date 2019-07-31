//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_RENDERER_PROJECTION_DIM_FWD_HPP_INCLUDED
#define SGE_RENDERER_PROJECTION_DIM_FWD_HPP_INCLUDED

#include <sge/renderer/scalar.hpp>
#include <fcppt/math/dim/static_fwd.hpp>


namespace sge
{
namespace renderer
{
namespace projection
{

typedef fcppt::math::dim::static_<
	sge::renderer::scalar,
	2
> dim;

}
}
}

#endif
