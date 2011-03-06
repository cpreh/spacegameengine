/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2011 Carl Philipp Reh (sefi@s-e-f-i.de)

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
*/


#ifndef SGE_D3D9_STATE_VISITOR_HPP_INCLUDED
#define SGE_D3D9_STATE_VISITOR_HPP_INCLUDED

#include "clear_fwd.hpp"
#include "../d3dinclude.hpp"
#include <sge/renderer/state/int.hpp>
#include <sge/renderer/state/uint.hpp>
#include <sge/renderer/state/float.hpp>
#include <sge/renderer/state/bool.hpp>
#include <sge/renderer/state/color.hpp>
#include <sge/renderer/state/cull_mode.hpp>
#include <sge/renderer/state/depth_func.hpp>
#include <sge/renderer/state/stencil_func.hpp>
#include <sge/renderer/state/alpha_func.hpp>
#include <sge/renderer/state/fog_mode.hpp>
#include <sge/renderer/state/draw_mode.hpp>
#include <sge/renderer/state/source_blend_func.hpp>
#include <sge/renderer/state/dest_blend_func.hpp>
#include <fcppt/nonassignable.hpp>

namespace sge
{
namespace d3d9
{
namespace state
{

class visitor
{
	FCPPT_NONASSIGNABLE(
		visitor
	);
public:
	visitor(
		IDirect3DDevice9 *,
		state::clear &
	);

	typedef void result_type;

	result_type
	operator()(
		sge::renderer::state::int_::type
	) const;

	result_type
	operator()(
		sge::renderer::state::uint::type
	) const;

	result_type
	operator()(
		sge::renderer::state::float_::type
	) const;

	result_type
	operator()(
		sge::renderer::state::bool_::type
	) const;

	result_type
	operator()(
		sge::renderer::state::color::type
	) const;

	result_type
	operator()(
		sge::renderer::state::cull_mode::type
	) const;

	result_type
	operator()(
		sge::renderer::state::depth_func::type
	) const;

	result_type
	operator()(
		sge::renderer::state::stencil_func::type
	) const;

	result_type
	operator()(
		sge::renderer::state::alpha_func::type
	) const;

	result_type
	operator()(
		sge::renderer::state::fog_mode::type
	) const;

	result_type
	operator()(
		sge::renderer::state::draw_mode::type
	) const;

	result_type
	operator()(
		sge::renderer::state::source_blend_func::type
	) const;

	result_type
	operator()(
		sge::renderer::state::dest_blend_func::type
	) const;
private:
	IDirect3DDevice9 *const device_;

	state::clear &clear_;
};

}
}
}

#endif
