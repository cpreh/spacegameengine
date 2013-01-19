/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2013 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#ifndef SGE_SCENIC_RENDER_CONTEXT_CG_LIGHT_POINT_HPP_INCLUDED
#define SGE_SCENIC_RENDER_CONTEXT_CG_LIGHT_POINT_HPP_INCLUDED

#include <sge/renderer/vector3.hpp>
#include <sge/scenic/render_context/ambient_color.hpp>
#include <sge/scenic/render_context/diffuse_color.hpp>
#include <sge/scenic/render_context/specular_color.hpp>
#include <sge/scenic/render_context/cg/light/index.hpp>
#include <sge/scenic/render_context/light/attenuation_fwd.hpp>
#include <sge/shader/parameter/vector.hpp>
#include <fcppt/noncopyable.hpp>


namespace sge
{
namespace scenic
{
namespace render_context
{
namespace cg
{
namespace light
{
class point
{
FCPPT_NONCOPYABLE(
	point);
public:
	point(
		sge::cg::program::object &,
		sge::scenic::render_context::cg::light::index const &);

	void
	diffuse_color(
		sge::scenic::render_context::diffuse_color const &);

	void
	specular_color(
		sge::scenic::render_context::specular_color const &);

	void
	ambient_color(
		sge::scenic::render_context::ambient_color const &);

	void
	camera_space_position(
		sge::renderer::vector3 const &);

	void
	attenuation(
		sge::scenic::render_context::light::attenuation const &);

	~point();
private:
	sge::shader::parameter::vector<sge::renderer::scalar,4> diffuse_color_;
	sge::shader::parameter::vector<sge::renderer::scalar,4> specular_color_;
	sge::shader::parameter::vector<sge::renderer::scalar,4> ambient_color_;
	sge::shader::parameter::vector<sge::renderer::scalar,3> camera_space_position_;
	sge::shader::parameter::vector<sge::renderer::scalar,3> attenuation_;
};
}
}
}
}
}

#endif
