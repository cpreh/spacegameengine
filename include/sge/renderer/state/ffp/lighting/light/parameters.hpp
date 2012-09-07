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


#ifndef SGE_RENDERER_STATE_FFP_LIGHTING_LIGHT_PARAMETERS_HPP_INCLUDED
#define SGE_RENDERER_STATE_FFP_LIGHTING_LIGHT_PARAMETERS_HPP_INCLUDED

#include <sge/image/color/any/object.hpp>
#include <sge/renderer/ambient_color.hpp>
#include <sge/renderer/diffuse_color.hpp>
#include <sge/renderer/specular_color.hpp>
#include <sge/renderer/symbol.hpp>
#include <sge/renderer/state/ffp/light/object_fwd.hpp>
#include <sge/renderer/state/ffp/light/variant.hpp>


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

class object
{
public:
	SGE_RENDERER_SYMBOL
	object(
		sge::renderer::state::ffp::lighting::diffuse_color const &,
		sge::renderer::state::ffp::lighting::specular_color const &,
		sge::renderer::state::ffp::lighting::ambient_color const &,
		sge::renderer::state::ffp::lighting::light::variant const &
	);

	SGE_RENDERER_SYMBOL
	sge::renderer::state::ffp::lighting::diffuse_color const &
	diffuse() const;

	SGE_RENDERER_SYMBOL
	sge::renderer::state::ffp::lighting::specular_color const &
	specular() const;

	SGE_RENDERER_SYMBOL
	sge::renderer::state::ffp::lighting::ambient_color const &
	ambient() const;

	SGE_RENDERER_SYMBOL
	sge::renderer::state::ffp::lighting::light::variant const &
	variant() const;
private:
	sge::renderer::state::ffp::lighting::diffuse_color diffuse_;

	sge::renderer::state::ffp::lighting::specular_color specular_;

	sge::renderer::state::ffp::lighting::ambient_color ambient_;

	sge::renderer::state::ffp::lighting::light::variant variant_;
};

}
}
}
}
}
}

#endif
