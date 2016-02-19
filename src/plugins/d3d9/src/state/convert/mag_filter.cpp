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
#include <sge/d3d9/state/convert/mag_filter.hpp>
#include <sge/renderer/state/core/sampler/filter/normal/mag.hpp>
#include <fcppt/assert/unreachable.hpp>


DWORD
sge::d3d9::state::convert::mag_filter(
	sge::renderer::state::core::sampler::filter::normal::mag const _type
)
{
	switch(
		_type
	)
	{
	case sge::renderer::state::core::sampler::filter::normal::mag::point:
		return D3DTEXF_POINT;
	case sge::renderer::state::core::sampler::filter::normal::mag::linear:
		return D3DTEXF_LINEAR;
	}

	FCPPT_ASSERT_UNREACHABLE;
}
