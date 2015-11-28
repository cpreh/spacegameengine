/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2015 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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


#ifndef SGE_OPENGL_VF_CLIENT_STATE_HPP_INCLUDED
#define SGE_OPENGL_VF_CLIENT_STATE_HPP_INCLUDED

#include <sge/opengl/common.hpp>
#include <sge/renderer/texture/stage.hpp>
#include <fcppt/config/external_begin.hpp>
#include <set>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace opengl
{
namespace vf
{

class client_state
{
public:
	typedef
	std::set<
		GLenum
	>
	normal_state_set;

	typedef
	std::set<
		sge::renderer::texture::stage
	>
	texture_state_set;

	typedef
	std::set<
		GLuint
	>
	index_state_set;

	client_state();

	void
	enable(
		GLenum
	);

	void
	disable(
		GLenum
	);

	void
	enable_texture(
		sge::renderer::texture::stage
	);

	void
	disable_texture(
		sge::renderer::texture::stage
	);

	void
	enable_attribute(
		GLuint
	);

	void
	disable_attribute(
		GLuint
	);

	normal_state_set const &
	normal_states() const;

	texture_state_set const &
	texture_states() const;

	index_state_set const &
	attribute_states() const;
private:
	normal_state_set normal_states_;

	texture_state_set texture_states_;

	index_state_set attribute_states_;
};

}
}
}

#endif
