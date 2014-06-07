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
	return mode_;
}

sge::renderer::state::ffp::fog::start const
sge::renderer::state::ffp::fog::enabled::start() const
{
	return start_;
}

sge::renderer::state::ffp::fog::end const
sge::renderer::state::ffp::fog::enabled::end() const
{
	return end_;
}

sge::renderer::state::ffp::fog::density const
sge::renderer::state::ffp::fog::enabled::density() const
{
	return density_;
}

sge::renderer::state::ffp::fog::color const
sge::renderer::state::ffp::fog::enabled::color() const
{
	return color_;
}
