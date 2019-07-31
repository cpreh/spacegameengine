//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/d3d9/d3dinclude.hpp>
#include <sge/d3d9/state/render.hpp>


sge::d3d9::state::render::render(
	D3DRENDERSTATETYPE const _state,
	DWORD const _value
)
:
	state_(
		_state
	),
	value_(
		_value
	)
{
}

D3DRENDERSTATETYPE
sge::d3d9::state::render::state() const
{
	return state_;
}

DWORD
sge::d3d9::state::render::value() const
{
	return value_;
}
