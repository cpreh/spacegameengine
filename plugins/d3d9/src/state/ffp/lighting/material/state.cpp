//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/d3d9/d3dinclude.hpp>
#include <sge/d3d9/state/ffp/lighting/material/state.hpp>


sge::d3d9::state::ffp::lighting::material::state::state(
	D3DMATERIAL9 const &_material
)
:
	material_(
		_material
	)
{
}

D3DMATERIAL9 const &
sge::d3d9::state::ffp::lighting::material::state::material() const
{
	return material_;
}
