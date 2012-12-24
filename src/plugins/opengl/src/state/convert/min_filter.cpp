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


#include <sge/opengl/common.hpp>
#include <sge/opengl/state/convert/min_filter.hpp>
#include <sge/renderer/state/core/sampler/filter/normal/min.hpp>
#include <sge/renderer/state/core/sampler/filter/normal/mip.hpp>
#include <fcppt/assert/unreachable.hpp>


GLenum
sge::opengl::state::convert::min_filter(
	sge::renderer::state::core::sampler::filter::normal::min const _min,
	sge::renderer::state::core::sampler::filter::normal::mip const _mip
)
{
	switch(
		_min
	)
	{
	case sge::renderer::state::core::sampler::filter::normal::min::point:
		switch(
			_mip
		)
		{
		case sge::renderer::state::core::sampler::filter::normal::mip::off:
			return GL_NEAREST;
		case sge::renderer::state::core::sampler::filter::normal::mip::point:
			return GL_NEAREST_MIPMAP_NEAREST;
		case sge::renderer::state::core::sampler::filter::normal::mip::linear:
			return GL_NEAREST_MIPMAP_LINEAR;
		}

		FCPPT_ASSERT_UNREACHABLE;
	case sge::renderer::state::core::sampler::filter::normal::min::linear:
		switch(
			_mip
		)
		{
		case sge::renderer::state::core::sampler::filter::normal::mip::off:
			return GL_LINEAR;
		case sge::renderer::state::core::sampler::filter::normal::mip::point:
			return GL_LINEAR_MIPMAP_NEAREST;
		case sge::renderer::state::core::sampler::filter::normal::mip::linear:
			return GL_LINEAR_MIPMAP_LINEAR;
		}

		FCPPT_ASSERT_UNREACHABLE;
	}

	FCPPT_ASSERT_UNREACHABLE;
}
