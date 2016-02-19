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


#ifndef SGE_OPENGL_VF_ATTRIBUTE_ACTOR_HPP_INCLUDED
#define SGE_OPENGL_VF_ATTRIBUTE_ACTOR_HPP_INCLUDED

#include <sge/opengl/common.hpp>
#include <sge/opengl/context/object_fwd.hpp>
#include <sge/opengl/vf/actor_parameters_fwd.hpp>
#include <sge/opengl/vf/attribute_config_fwd.hpp>
#include <sge/opengl/vf/client_state_combiner_fwd.hpp>
#include <sge/opengl/vf/pointer.hpp>
#include <sge/opengl/vf/pointer_actor.hpp>
#include <sge/renderer/vf/dynamic/extra_fwd.hpp>
#include <fcppt/noncopyable.hpp>


namespace sge
{
namespace opengl
{
namespace vf
{

class attribute_actor
:
	public sge::opengl::vf::pointer_actor
{
	FCPPT_NONCOPYABLE(
		attribute_actor
	);
public:
	attribute_actor(
		sge::opengl::vf::actor_parameters const &,
		sge::renderer::vf::dynamic::extra const &
	);

	~attribute_actor()
	override;
private:
	void
	operator()(
		sge::opengl::vf::client_state_combiner &,
		sge::opengl::vf::pointer
	) const
	override;

	void
	unuse(
		sge::opengl::vf::client_state_combiner &
	) const
	override;

	sge::opengl::vf::attribute_config const &attribute_config_;

	GLint const elements_;

	GLenum const format_;

	GLuint const location_;
};

}
}
}

#endif
