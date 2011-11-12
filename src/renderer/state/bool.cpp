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


#include <sge/renderer/state/bool.hpp>
#include <sge/src/renderer/state/define_trampoline_object.hpp>
#include <sge/src/renderer/state/instantiate_with_trampoline.hpp>


SGE_RENDERER_STATE_INSTANTIATE_WITH_TRAMPOLINE(bool_)
SGE_RENDERER_STATE_DEFINE_TRAMPOLINE_OBJECT(bool_, clear_depth_buffer)
SGE_RENDERER_STATE_DEFINE_TRAMPOLINE_OBJECT(bool_, clear_back_buffer)
SGE_RENDERER_STATE_DEFINE_TRAMPOLINE_OBJECT(bool_, clear_stencil_buffer)
SGE_RENDERER_STATE_DEFINE_TRAMPOLINE_OBJECT(bool_, enable_alpha_blending)
SGE_RENDERER_STATE_DEFINE_TRAMPOLINE_OBJECT(bool_, enable_lighting)
SGE_RENDERER_STATE_DEFINE_TRAMPOLINE_OBJECT(bool_, enable_multi_sampling)
SGE_RENDERER_STATE_DEFINE_TRAMPOLINE_OBJECT(bool_, enable_point_sprites)
SGE_RENDERER_STATE_DEFINE_TRAMPOLINE_OBJECT(bool_, enable_scissor_test)
SGE_RENDERER_STATE_DEFINE_TRAMPOLINE_OBJECT(bool_, write_to_depth_buffer)
SGE_RENDERER_STATE_DEFINE_TRAMPOLINE_OBJECT(bool_, write_alpha)
SGE_RENDERER_STATE_DEFINE_TRAMPOLINE_OBJECT(bool_, write_blue)
SGE_RENDERER_STATE_DEFINE_TRAMPOLINE_OBJECT(bool_, write_green)
SGE_RENDERER_STATE_DEFINE_TRAMPOLINE_OBJECT(bool_, write_red)
