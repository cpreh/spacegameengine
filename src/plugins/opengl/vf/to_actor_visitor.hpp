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


#ifndef SGE_OPENGL_VF_TO_ACTOR_VISITOR_HPP_INCLUDED
#define SGE_OPENGL_VF_TO_ACTOR_VISITOR_HPP_INCLUDED

#include "actor_ptr.hpp"
#include "actor_parameters.hpp"
#include <sge/renderer/vf/dynamic/pos_fwd.hpp>
#include <sge/renderer/vf/dynamic/normal_fwd.hpp>
#include <sge/renderer/vf/dynamic/color_fwd.hpp>
#include <sge/renderer/vf/dynamic/texpos_fwd.hpp>
#include <sge/renderer/vf/dynamic/unspecified_fwd.hpp>
#include <fcppt/nonassignable.hpp>

namespace sge
{
namespace opengl
{
namespace vf
{

class to_actor_visitor
{
	FCPPT_NONASSIGNABLE(
		to_actor_visitor
	)
public:
	explicit to_actor_visitor(
		actor_parameters const &
	);

	typedef sge::opengl::vf::actor_ptr result_type;

	result_type
	operator()(
		sge::renderer::vf::dynamic::pos const &
	) const;

	result_type
	operator()(
		sge::renderer::vf::dynamic::normal const &
	) const;

	result_type
	operator()(
		sge::renderer::vf::dynamic::color const &
	) const;

	result_type
	operator()(
		sge::renderer::vf::dynamic::texpos const &
	) const;

	result_type
	operator()(
		sge::renderer::vf::dynamic::unspecified const &
	) const;
private:
	actor_parameters const parameters_;
};

}
}
}

#endif
