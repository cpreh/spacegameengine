/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2009 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#ifndef SGE_OPENGL_VF_NORMAL_ACTOR_HPP_INCLUDED
#define SGE_OPENGL_VF_NORMAL_ACTOR_HPP_INCLUDED

#include "pointer_actor.hpp"
#include "client_state_combiner_fwd.hpp"
#include <sge/renderer/vf/vertex_size.hpp>
#include <sge/renderer/vf/dynamic/ordered_element_fwd.hpp>

namespace sge
{
namespace opengl
{
namespace vf
{

class normal_actor
:
	public pointer_actor
{
public:
	normal_actor(
		renderer::vf::dynamic::ordered_element const &,
		renderer::vf::vertex_size stride
	);
private:
	void
	operator()(
		client_state_combiner &
	) const;
};

}
}
}

#endif
