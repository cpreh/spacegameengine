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


#ifndef SGE_OPENGL_STATE_CORE_BLEND_ALPHA_VISITOR_HPP_INCLUDED
#define SGE_OPENGL_STATE_CORE_BLEND_ALPHA_VISITOR_HPP_INCLUDED

#include <sge/opengl/context/object_fwd.hpp>
#include <sge/opengl/state/actor_vector.hpp>
#include <sge/renderer/state/core/blend/alpha_enabled_fwd.hpp>
#include <sge/renderer/state/core/blend/alpha_off_fwd.hpp>
#include <fcppt/nonassignable.hpp>


namespace sge
{
namespace opengl
{
namespace state
{
namespace core
{
namespace blend
{

class alpha_visitor
{
	FCPPT_NONASSIGNABLE(
		alpha_visitor
	);
public:
	// TODO: Use match
	explicit
	alpha_visitor(
		sge::opengl::context::object &
	);

	typedef sge::opengl::state::actor_vector result_type;

	result_type
	operator()(
		sge::renderer::state::core::blend::alpha_off const &
	) const;

	result_type
	operator()(
		sge::renderer::state::core::blend::alpha_enabled const &
	) const;
private:
	sge::opengl::context::object &context_;
};

}
}
}
}
}

#endif
