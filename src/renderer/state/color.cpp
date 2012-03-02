/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2012 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#include <sge/image/color/any/object.hpp>
#include <sge/renderer/state/color.hpp>
#include <sge/src/renderer/state/define_trampoline_object.hpp>
#include <sge/src/renderer/state/instantiate_with_trampoline.hpp>


/*
SGE_RENDERER_STATE_INSTANTIATE_WITH_TRAMPOLINE(color)
SGE_RENDERER_STATE_DEFINE_TRAMPOLINE_OBJECT(color, back_buffer_clear_color)
SGE_RENDERER_STATE_DEFINE_TRAMPOLINE_OBJECT(color, ambient_light_color)
SGE_RENDERER_STATE_DEFINE_TRAMPOLINE_OBJECT(color, fog_color)
*/

template class __attribute__ ((visibility("default"))) sge::renderer::state::var< sge::renderer::state::color::base_type, sge::renderer::state::color::available_states::type>;
template class __attribute__ ((visibility("default"))) sge::renderer::state::trampoline< sge::renderer::state::color::base_type, sge::renderer::state::color::available_states::type>;
template __attribute__ ((visibility("default"))) sge::renderer::state::color::base_type sge::renderer::state::extract_trampoline( sge::renderer::state::list const &, sge::renderer::state::trampoline< color::base_type, color::available_states::type > const &);

sge::renderer::state::color::trampoline const sge::renderer::state::color::back_buffer_clear_color( sge::renderer::state::color::available_states::back_buffer_clear_color);
sge::renderer::state::color::trampoline const sge::renderer::state::color::ambient_light_color( sge::renderer::state::color::available_states::ambient_light_color);
sge::renderer::state::color::trampoline const sge::renderer::state::color::fog_color( sge::renderer::state::color::available_states::fog_color);
