//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/renderer/state/core/sampler/filter/anisotropic/level.hpp>
#include <sge/renderer/state/core/sampler/filter/anisotropic/mip.hpp>
#include <sge/renderer/state/core/sampler/filter/anisotropic/parameters.hpp>


sge::renderer::state::core::sampler::filter::anisotropic::parameters::parameters(
	sge::renderer::state::core::sampler::filter::anisotropic::mip const _mip,
	sge::renderer::state::core::sampler::filter::anisotropic::level const _level
)
:
	mip_(
		_mip
	),
	level_(
		_level
	)
{
}

sge::renderer::state::core::sampler::filter::anisotropic::mip
sge::renderer::state::core::sampler::filter::anisotropic::parameters::mip() const
{
	return
		mip_;
}

sge::renderer::state::core::sampler::filter::anisotropic::level
sge::renderer::state::core::sampler::filter::anisotropic::parameters::level() const
{
	return
		level_;
}

bool
sge::renderer::state::core::sampler::filter::anisotropic::operator==(
	sge::renderer::state::core::sampler::filter::anisotropic::parameters const &_left,
	sge::renderer::state::core::sampler::filter::anisotropic::parameters const &_right
)
{
	return
		_left.mip() == _right.mip()
		&&
		_left.level() == _right.level();
}
