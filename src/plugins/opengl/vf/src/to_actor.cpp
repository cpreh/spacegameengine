/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2007  Carl Philipp Reh (sefi@s-e-f-i.de)

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


#include "../to_actor.hpp"
#include "../pos_actor.hpp"
#include "../normal_actor.hpp"
#include "../color_actor.hpp"
#include "../texpos_actor.hpp"
#include <sge/renderer/vf/dynamic_ordered_element.hpp>
#include <sge/exception.hpp>
#include <sge/text.hpp>

sge::ogl::vf::actor_ptr 
sge::ogl::vf::to_actor(
	renderer::vf::dynamic_ordered_element const &e,
	renderer::vf::vertex_size const stride)
{
	switch(e.element().role()) {
	case renderer::vf::role::pos:
		return actor_ptr(
			new pos_actor(e, stride));
	case renderer::vf::role::normal:
		return actor_ptr(
			new normal_actor(e, stride));
	case renderer::vf::role::color:
		return actor_ptr(
			new color_actor(e, stride));
	case renderer::vf::role::texpos:
		return actor_ptr(
			new texpos_actor(e, stride));
	default:
		throw exception(
			SGE_TEXT("Invalid role in ogl vertex format!"));
	}
}
