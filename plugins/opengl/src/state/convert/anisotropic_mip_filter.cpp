//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/opengl/common.hpp>
#include <sge/opengl/state/convert/anisotropic_mip_filter.hpp>
#include <sge/renderer/state/core/sampler/filter/anisotropic/mip.hpp>
#include <fcppt/assert/unreachable.hpp>


GLenum
sge::opengl::state::convert::anisotropic_mip_filter(
	sge::renderer::state::core::sampler::filter::anisotropic::mip const _filter
)
{
	switch(
		_filter
	)
	{
	case sge::renderer::state::core::sampler::filter::anisotropic::mip::off:
		return GL_NEAREST;
	case sge::renderer::state::core::sampler::filter::anisotropic::mip::point:
		return GL_NEAREST_MIPMAP_NEAREST;
	case sge::renderer::state::core::sampler::filter::anisotropic::mip::linear:
		return GL_NEAREST_MIPMAP_LINEAR;
	}

	FCPPT_ASSERT_UNREACHABLE;
}
