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


#ifndef SGE_OPENGL_VF_POINTER_ACTOR_HPP_INCLUDED
#define SGE_OPENGL_VF_POINTER_ACTOR_HPP_INCLUDED

#include <sge/opengl/vf/actor.hpp>
#include <sge/opengl/vf/actor_parameters_fwd.hpp>
#include <sge/renderer/vf/dynamic/offset.hpp>
#include <sge/renderer/vf/dynamic/stride.hpp>
#include <fcppt/noncopyable.hpp>


namespace sge
{
namespace opengl
{
namespace vf
{

class pointer_actor
:
	public sge::opengl::vf::actor
{
	FCPPT_NONCOPYABLE(
		pointer_actor
	);
public:
	virtual
	~pointer_actor() = 0;
protected:
	explicit
	pointer_actor(
		sge::opengl::vf::actor_parameters const &
	);

	sge::renderer::vf::dynamic::offset const
	offset() const;

	sge::renderer::vf::dynamic::stride const
	stride() const;
private:
	sge::renderer::vf::dynamic::offset const offset_;

	sge::renderer::vf::dynamic::stride const stride_;
};

}
}
}

#endif
