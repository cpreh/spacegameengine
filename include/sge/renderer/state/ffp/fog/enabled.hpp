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


#ifndef SGE_RENDERER_STATE_FFP_FOG_ENABLED_HPP_INCLUDED
#define SGE_RENDERER_STATE_FFP_FOG_ENABLED_HPP_INCLUDED

#include <sge/renderer/detail/symbol.hpp>
#include <sge/renderer/state/ffp/fog/color.hpp>
#include <sge/renderer/state/ffp/fog/density.hpp>
#include <sge/renderer/state/ffp/fog/enabled_fwd.hpp>
#include <sge/renderer/state/ffp/fog/end.hpp>
#include <sge/renderer/state/ffp/fog/mode.hpp>
#include <sge/renderer/state/ffp/fog/start.hpp>


namespace sge
{
namespace renderer
{
namespace state
{
namespace ffp
{
namespace fog
{

class enabled
{
public:
	SGE_RENDERER_DETAIL_SYMBOL
	enabled(
		sge::renderer::state::ffp::fog::mode,
		sge::renderer::state::ffp::fog::start,
		sge::renderer::state::ffp::fog::end,
		sge::renderer::state::ffp::fog::density,
		sge::renderer::state::ffp::fog::color
	);

	SGE_RENDERER_DETAIL_SYMBOL
	sge::renderer::state::ffp::fog::mode
	mode() const;

	SGE_RENDERER_DETAIL_SYMBOL
	sge::renderer::state::ffp::fog::start
	start() const;

	SGE_RENDERER_DETAIL_SYMBOL
	sge::renderer::state::ffp::fog::end
	end() const;

	SGE_RENDERER_DETAIL_SYMBOL
	sge::renderer::state::ffp::fog::density
	density() const;

	SGE_RENDERER_DETAIL_SYMBOL
	sge::renderer::state::ffp::fog::color
	color() const;
private:
	sge::renderer::state::ffp::fog::mode mode_;

	sge::renderer::state::ffp::fog::start start_;

	sge::renderer::state::ffp::fog::end end_;

	sge::renderer::state::ffp::fog::density density_;

	sge::renderer::state::ffp::fog::color color_;
};

}
}
}
}
}

#endif
