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


#ifndef SGE_RENDERER_STATE_FFP_LIGHTING_LIGHT_SPOT_HPP_INCLUDED
#define SGE_RENDERER_STATE_FFP_LIGHTING_LIGHT_SPOT_HPP_INCLUDED

#include <sge/renderer/detail/symbol.hpp>
#include <sge/renderer/state/ffp/lighting/light/attenuation.hpp>
#include <sge/renderer/state/ffp/lighting/light/cutoff_angle.hpp>
#include <sge/renderer/state/ffp/lighting/light/direction.hpp>
#include <sge/renderer/state/ffp/lighting/light/position.hpp>
#include <sge/renderer/state/ffp/lighting/light/spot_fwd.hpp>


namespace sge
{
namespace renderer
{
namespace state
{
namespace ffp
{
namespace lighting
{
namespace light
{

class spot
{
public:
	SGE_RENDERER_DETAIL_SYMBOL
	spot(
		sge::renderer::state::ffp::lighting::light::position const &,
		sge::renderer::state::ffp::lighting::light::direction const &,
		sge::renderer::state::ffp::lighting::light::cutoff_angle,
		sge::renderer::state::ffp::lighting::light::attenuation const &
	);

	SGE_RENDERER_DETAIL_SYMBOL
	sge::renderer::state::ffp::lighting::light::position const &
	position() const;

	SGE_RENDERER_DETAIL_SYMBOL
	sge::renderer::state::ffp::lighting::light::direction const &
	direction() const;

	SGE_RENDERER_DETAIL_SYMBOL
	sge::renderer::state::ffp::lighting::light::cutoff_angle
	cutoff_angle() const;

	SGE_RENDERER_DETAIL_SYMBOL
	sge::renderer::state::ffp::lighting::light::attenuation const &
	attenuation() const;
private:
	sge::renderer::state::ffp::lighting::light::position position_;

	sge::renderer::state::ffp::lighting::light::direction direction_;

	sge::renderer::state::ffp::lighting::light::cutoff_angle cutoff_angle_;

	sge::renderer::state::ffp::lighting::light::attenuation attenuation_;
};

}
}
}
}
}
}

#endif
