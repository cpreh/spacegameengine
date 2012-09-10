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


#ifndef SGE_SCENIC_RENDER_CONTEXT_CG_POINT_LIGHT_HPP_INCLUDED
#define SGE_SCENIC_RENDER_CONTEXT_CG_POINT_LIGHT_HPP_INCLUDED

#include <sge/renderer/ambient_color.hpp>
#include <sge/renderer/diffuse_color.hpp>
#include <sge/renderer/specular_color.hpp>
#include <sge/renderer/vector3.hpp>
#include <sge/renderer/light/attenuation_fwd.hpp>
#include <sge/shader/parameter/vector.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/config/external_begin.hpp>
#include <cstddef>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace scenic
{
namespace render_context
{
namespace cg
{
class point_light
{
FCPPT_NONCOPYABLE(
	point_light);
public:
	FCPPT_MAKE_STRONG_TYPEDEF(
		std::size_t,
		index);

	point_light(
		sge::cg::program::object &,
		index const &);

	void
	diffuse_color(
		sge::renderer::diffuse_color const &);

	void
	specular_color(
		sge::renderer::specular_color const &);

	void
	ambient_color(
		sge::renderer::ambient_color const &);

	void
	camera_space_position(
		sge::renderer::vector3 const &);

	void
	attenuation(
		sge::renderer::light::attenuation const &);

	~point_light();
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

#endif
