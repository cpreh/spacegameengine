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



#include <sge/renderer/state/states.hpp>
#include <sge/renderer/state/traits.hpp>

#define SGE_DEFINE_STATE_TRAMPOLINE(s, x)\
sge::renderer::state::s::trampoline_type const \
sge::renderer::state::s::x(\
	sge::renderer::state::traits<\
		sge::renderer::state::s::base_type\
	>::x);

SGE_DEFINE_STATE_TRAMPOLINE(int_, stencil_clear_val)
SGE_DEFINE_STATE_TRAMPOLINE(int_, stencil_ref)

SGE_DEFINE_STATE_TRAMPOLINE(uint_, stencil_mask)

SGE_DEFINE_STATE_TRAMPOLINE(float_, zbuffer_clear_val)
SGE_DEFINE_STATE_TRAMPOLINE(float_, alpha_test_ref)
SGE_DEFINE_STATE_TRAMPOLINE(float_, fog_start)
SGE_DEFINE_STATE_TRAMPOLINE(float_, fog_end)
SGE_DEFINE_STATE_TRAMPOLINE(float_, fog_density)

SGE_DEFINE_STATE_TRAMPOLINE(bool_, clear_zbuffer)
SGE_DEFINE_STATE_TRAMPOLINE(bool_, clear_backbuffer)
SGE_DEFINE_STATE_TRAMPOLINE(bool_, clear_stencil)
SGE_DEFINE_STATE_TRAMPOLINE(bool_, enable_alpha_blending)
SGE_DEFINE_STATE_TRAMPOLINE(bool_, enable_lighting)

SGE_DEFINE_STATE_TRAMPOLINE(color_, clear_color)
SGE_DEFINE_STATE_TRAMPOLINE(color_, ambient_light_color)
SGE_DEFINE_STATE_TRAMPOLINE(color_, fog_color)

#undef SGE_DEFINE_STATE_TRAMPOLINE
