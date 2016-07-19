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


#ifndef SGE_OPENGL_VF_TEXPOS_ACTOR_HPP_INCLUDED
#define SGE_OPENGL_VF_TEXPOS_ACTOR_HPP_INCLUDED

#include <sge/opengl/common.hpp>
#include <sge/opengl/context/object_fwd.hpp>
#include <sge/opengl/vf/actor_parameters_fwd.hpp>
#include <sge/opengl/vf/pointer.hpp>
#include <sge/opengl/vf/pointer_actor.hpp>
#include <sge/renderer/texture/stage.hpp>
#include <sge/renderer/vf/dynamic/texpos_fwd.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/log/object_fwd.hpp>


namespace sge
{
namespace opengl
{
namespace vf
{

class texpos_actor
:
	public sge::opengl::vf::pointer_actor
{
	FCPPT_NONCOPYABLE(
		texpos_actor
	);
public:
	texpos_actor(
		fcppt::log::object &,
		sge::opengl::vf::actor_parameters const &,
		sge::renderer::vf::dynamic::texpos const &
	);

	~texpos_actor()
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

	fcppt::log::object &log_;

	sge::opengl::context::object &context_;

	GLint const elements_;

	GLenum const format_;

	sge::renderer::texture::stage const index_;
};

}
}
}

#endif
