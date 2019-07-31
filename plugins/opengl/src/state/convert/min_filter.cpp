//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


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
			return
				GL_NEAREST;
		case sge::renderer::state::core::sampler::filter::normal::mip::point:
			return
				GL_NEAREST_MIPMAP_NEAREST;
		case sge::renderer::state::core::sampler::filter::normal::mip::linear:
			return
				GL_NEAREST_MIPMAP_LINEAR;
		}

		FCPPT_ASSERT_UNREACHABLE;
	case sge::renderer::state::core::sampler::filter::normal::min::linear:
		switch(
			_mip
		)
		{
		case sge::renderer::state::core::sampler::filter::normal::mip::off:
			return
				GL_LINEAR;
		case sge::renderer::state::core::sampler::filter::normal::mip::point:
			return
				GL_LINEAR_MIPMAP_NEAREST;
		case sge::renderer::state::core::sampler::filter::normal::mip::linear:
			return
				GL_LINEAR_MIPMAP_LINEAR;
		}

		FCPPT_ASSERT_UNREACHABLE;
	}

	FCPPT_ASSERT_UNREACHABLE;
}
