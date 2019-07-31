//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/renderer/state/ffp/fog/color.hpp>
#include <sge/renderer/state/ffp/fog/density.hpp>
#include <sge/renderer/state/ffp/fog/enabled.hpp>
#include <sge/renderer/state/ffp/fog/end.hpp>
#include <sge/renderer/state/ffp/fog/mode.hpp>
#include <sge/renderer/state/ffp/fog/start.hpp>


sge::renderer::state::ffp::fog::enabled::enabled(
	sge::renderer::state::ffp::fog::mode const _mode,
	sge::renderer::state::ffp::fog::start const _start,
	sge::renderer::state::ffp::fog::end const _end,
	sge::renderer::state::ffp::fog::density const _density,
	sge::renderer::state::ffp::fog::color const _color
)
:
	mode_(
		_mode
	),
	start_(
		_start
	),
	end_(
		_end
	),
	density_(
		_density
	),
	color_(
		_color
	)
{
}

sge::renderer::state::ffp::fog::mode
sge::renderer::state::ffp::fog::enabled::mode() const
{
	return
		mode_;
}

sge::renderer::state::ffp::fog::start
sge::renderer::state::ffp::fog::enabled::start() const
{
	return
		start_;
}

sge::renderer::state::ffp::fog::end
sge::renderer::state::ffp::fog::enabled::end() const
{
	return
		end_;
}

sge::renderer::state::ffp::fog::density
sge::renderer::state::ffp::fog::enabled::density() const
{
	return
		density_;
}

sge::renderer::state::ffp::fog::color
sge::renderer::state::ffp::fog::enabled::color() const
{
	return
		color_;
}
