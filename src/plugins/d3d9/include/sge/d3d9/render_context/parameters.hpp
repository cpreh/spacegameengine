/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2012 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#ifndef SGE_D3D9_RENDER_CONTEXT_PARAMETERS_HPP_INCLUDED
#define SGE_D3D9_RENDER_CONTEXT_PARAMETERS_HPP_INCLUDED

#include <sge/d3d9/d3dinclude.hpp>
#include <sge/d3d9/render_context/parameters_fwd.hpp>
#include <sge/d3d9/state/core/defaults_fwd.hpp>
#include <sge/d3d9/state/ffp/defaults_fwd.hpp>
#include <sge/renderer/caps/light_indices.hpp>
#include <sge/renderer/caps/texture_stages.hpp>
#include <sge/renderer/target/base_fwd.hpp>
#include <fcppt/nonassignable.hpp>


namespace sge
{
namespace d3d9
{
namespace render_context
{

class parameters
{
	FCPPT_NONASSIGNABLE(
		parameters
	);
public:
	parameters(
		IDirect3DDevice9 &,
		sge::renderer::target::base &,
		sge::renderer::caps::texture_stages,
		sge::renderer::caps::light_indices,
		sge::d3d9::state::core::defaults const &,
		sge::d3d9::state::ffp::defaults const &
	);

	IDirect3DDevice9 &
	device() const;

	sge::renderer::target::base &
	target() const;

	sge::renderer::caps::texture_stages const
	texture_stages() const;

	sge::renderer::caps::light_indices const
	light_indices() const;

	sge::d3d9::state::core::defaults const &
	core_defaults() const;

	sge::d3d9::state::ffp::defaults const &
	ffp_defaults() const;
private:
	IDirect3DDevice9 &device_;

	sge::renderer::target::base &target_;

	sge::renderer::caps::texture_stages const texture_stages_;

	sge::renderer::caps::light_indices const light_indices_;

	sge::d3d9::state::core::defaults const &core_defaults_;

	sge::d3d9::state::ffp::defaults const &ffp_defaults_;
};

}
}
}

#endif
