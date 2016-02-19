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


#ifndef SGE_OPENGL_STATE_CORE_DEPTH_STENCIL_STENCIL_ENABLED_VISITOR_HPP_INCLUDED
#define SGE_OPENGL_STATE_CORE_DEPTH_STENCIL_STENCIL_ENABLED_VISITOR_HPP_INCLUDED

#include <sge/opengl/context/object_fwd.hpp>
#include <sge/opengl/state/actor_vector.hpp>
#include <sge/renderer/state/core/depth_stencil/stencil/combined_fwd.hpp>
#include <sge/renderer/state/core/depth_stencil/stencil/read_mask.hpp>
#include <sge/renderer/state/core/depth_stencil/stencil/ref.hpp>
#include <sge/renderer/state/core/depth_stencil/stencil/separate_fwd.hpp>
#include <sge/renderer/state/core/depth_stencil/stencil/write_mask.hpp>
#include <fcppt/nonassignable.hpp>


namespace sge
{
namespace opengl
{
namespace state
{
namespace core
{
namespace depth_stencil
{
namespace stencil
{

class enabled_visitor
{
	FCPPT_NONASSIGNABLE(
		enabled_visitor
	);
public:
	// TODO: match
	enabled_visitor(
		sge::opengl::context::object &,
		sge::renderer::state::core::depth_stencil::stencil::ref,
		sge::renderer::state::core::depth_stencil::stencil::read_mask,
		sge::renderer::state::core::depth_stencil::stencil::write_mask
	);

	typedef sge::opengl::state::actor_vector result_type;

	result_type
	operator()(
		sge::renderer::state::core::depth_stencil::stencil::combined const &
	) const;

	result_type
	operator()(
		sge::renderer::state::core::depth_stencil::stencil::separate const &
	) const;
private:
	sge::opengl::context::object &context_;

	sge::renderer::state::core::depth_stencil::stencil::ref const ref_;

	sge::renderer::state::core::depth_stencil::stencil::read_mask const read_mask_;

	sge::renderer::state::core::depth_stencil::stencil::write_mask const write_mask_;
};

}
}
}
}
}
}

#endif
