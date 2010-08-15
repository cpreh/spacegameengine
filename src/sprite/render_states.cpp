/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2010 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#include <sge/sprite/render_states.hpp>
#include <sge/renderer/state/list.hpp>
#include <sge/renderer/state/var.hpp>
#include <sge/renderer/state/trampoline.hpp>

sge::renderer::state::list const &
sge::sprite::render_states()
{
	static renderer::state::list const states_ = renderer::state::list
		(renderer::state::bool_::enable_alpha_blending = true)
		(renderer::state::source_blend_func::src_alpha)
		(renderer::state::dest_blend_func::inv_src_alpha)
		(renderer::state::cull_mode::off)
		(renderer::state::depth_func::off)
		(renderer::state::stencil_func::off)
		(renderer::state::draw_mode::fill);
	return states_;
}
