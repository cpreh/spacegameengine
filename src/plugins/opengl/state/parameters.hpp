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


#ifndef SGE_OPENGL_STATE_PARAMETERS_HPP_INCLUDED
#define SGE_OPENGL_STATE_PARAMETERS_HPP_INCLUDED

#include "parameters_fwd.hpp"
#include "deferred/object_fwd.hpp"
#include "../context/object_fwd.hpp"
#include "../multi_sample_context_fwd.hpp"
#include "../point_sprite_context_fwd.hpp"
#include <sge/renderer/depth_stencil_buffer.hpp>
#include <fcppt/nonassignable.hpp>

namespace sge
{
namespace opengl
{
namespace state
{

class parameters
{
	FCPPT_NONASSIGNABLE(
		parameters
	);
public:
	parameters(
		opengl::context::object &,
		state::deferred::object &,
		renderer::depth_stencil_buffer::type
	);

	opengl::multi_sample_context &
	multi_sample_context() const;

	opengl::point_sprite_context &
	point_sprite_context() const;

	state::deferred::object &
	deferred() const;

	renderer::depth_stencil_buffer::type
	depth_stencil_buffer() const;
private:
	opengl::multi_sample_context &multi_sample_context_;

	opengl::point_sprite_context &point_sprite_context_;

	state::deferred::object &deferred_;

	renderer::depth_stencil_buffer::type const depth_stencil_buffer_;
};

}
}
}

#endif
