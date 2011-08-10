/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2011 Carl Philipp Reh (sefi@s-e-f-i.de)

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

#include "../common.hpp"
#include <sge/renderer/stage.hpp>
#include <fcppt/container/index_map.hpp>
#include <fcppt/tr1/unordered_set.hpp>
#include <set>

namespace sge
{
namespace opengl
{
namespace vf
{

class client_state
{
public:
	typedef std::tr1::unordered_set<
		GLenum
	> normal_state_set;

	// use until we have a good way to define hashes
	typedef std::set<
		renderer::stage
	> texture_state_set;

	typedef std::tr1::unordered_set<
		GLuint
	> index_state_set;

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
		renderer::stage
	);

	void
	disable_texture(
		renderer::stage
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
