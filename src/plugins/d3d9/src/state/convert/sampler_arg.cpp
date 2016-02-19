/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2016 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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
#include <sge/d3d9/state/convert/sampler_arg.hpp>
#include <sge/renderer/state/ffp/sampler/arg.hpp>
#include <fcppt/assert/unreachable.hpp>


DWORD
sge::d3d9::state::convert::sampler_arg(
	sge::renderer::state::ffp::sampler::arg const _arg
)
{
	switch(
		_arg
	)
	{
	case sge::renderer::state::ffp::sampler::arg::constant:
		return D3DTA_CONSTANT;
	case sge::renderer::state::ffp::sampler::arg::previous:
		return D3DTA_CURRENT;
//		return D3DTA_SPECULAR;
//		return D3DTA_TEMP;
	case sge::renderer::state::ffp::sampler::arg::texture:
		return D3DTA_TEXTURE;
	case sge::renderer::state::ffp::sampler::arg::vertex_color:
		// TODO: Is this correct?
		return D3DTA_DIFFUSE;
	}

	FCPPT_ASSERT_UNREACHABLE;
}
