/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2014 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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


#include <sge/d3d9/d3dinclude.hpp>
#include <sge/d3d9/state/convert/anisotropic_mip_filter.hpp>
#include <sge/d3d9/state/convert/mag_filter.hpp>
#include <sge/d3d9/state/convert/min_filter.hpp>
#include <sge/d3d9/state/convert/normal_mip_filter.hpp>
#include <sge/d3d9/state/core/sampler/state.hpp>
#include <sge/d3d9/state/core/sampler/state_vector.hpp>
#include <sge/d3d9/state/core/sampler/filter/visitor.hpp>
#include <sge/renderer/state/core/sampler/filter/anisotropic/parameters.hpp>
#include <sge/renderer/state/core/sampler/filter/normal/parameters.hpp>


sge::d3d9::state::core::sampler::filter::visitor::result_type const
sge::d3d9::state::core::sampler::filter::visitor::operator()(
	sge::renderer::state::core::sampler::filter::anisotropic::parameters const &_anisotropic
) const
{
	return
		sge::d3d9::state::core::sampler::state_vector{
			sge::d3d9::state::core::sampler::state(
				D3DSAMP_MAGFILTER,
				D3DTEXF_ANISOTROPIC
			),
			sge::d3d9::state::core::sampler::state(
				D3DSAMP_MINFILTER,
				D3DTEXF_ANISOTROPIC
			),
			sge::d3d9::state::core::sampler::state(
				D3DSAMP_MIPFILTER,
				sge::d3d9::state::convert::anisotropic_mip_filter(
					_anisotropic.mip()
				)
			),
			sge::d3d9::state::core::sampler::state(
				D3DSAMP_MAXANISOTROPY,
				_anisotropic.level().get()
			)
		};
}

sge::d3d9::state::core::sampler::filter::visitor::result_type const
sge::d3d9::state::core::sampler::filter::visitor::operator()(
	sge::renderer::state::core::sampler::filter::normal::parameters const &_normal
) const
{
	return
		sge::d3d9::state::core::sampler::state_vector{
			sge::d3d9::state::core::sampler::state(
				D3DSAMP_MAGFILTER,
				sge::d3d9::state::convert::mag_filter(
					_normal.mag()
				)
			),
			sge::d3d9::state::core::sampler::state(
				D3DSAMP_MINFILTER,
				sge::d3d9::state::convert::min_filter(
					_normal.min()
				)
			),
			sge::d3d9::state::core::sampler::state(
				D3DSAMP_MIPFILTER,
				sge::d3d9::state::convert::normal_mip_filter(
					_normal.mip()
				)
			),
			sge::d3d9::state::core::sampler::state(
				D3DSAMP_MAXANISOTROPY,
				1u
			)
		};
}
