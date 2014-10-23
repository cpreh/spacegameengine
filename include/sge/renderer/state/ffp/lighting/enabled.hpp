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


#ifndef SGE_RENDERER_STATE_FFP_LIGHTING_ENABLED_HPP_INCLUDED
#define SGE_RENDERER_STATE_FFP_LIGHTING_ENABLED_HPP_INCLUDED

#include <sge/renderer/detail/symbol.hpp>
#include <sge/renderer/state/ffp/lighting/ambient_color.hpp>
#include <sge/renderer/state/ffp/lighting/diffuse_from_vertex.hpp>
#include <sge/renderer/state/ffp/lighting/enabled_fwd.hpp>


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

class enabled
{
public:
	SGE_RENDERER_DETAIL_SYMBOL
	enabled(
		sge::renderer::state::ffp::lighting::ambient_color const &,
		sge::renderer::state::ffp::lighting::diffuse_from_vertex
	);

	SGE_RENDERER_DETAIL_SYMBOL
	sge::renderer::state::ffp::lighting::ambient_color const &
	ambient_color() const;

	SGE_RENDERER_DETAIL_SYMBOL
	sge::renderer::state::ffp::lighting::diffuse_from_vertex const
	diffuse_from_vertex() const;
private:
	sge::renderer::state::ffp::lighting::ambient_color ambient_color_;

	sge::renderer::state::ffp::lighting::diffuse_from_vertex diffuse_from_vertex_;
};

}
}
}
}
}

#endif
