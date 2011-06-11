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


#ifndef SGE_RENDERER_STATE_STATE_HPP_INCLUDED
#define SGE_RENDERER_STATE_STATE_HPP_INCLUDED

#include <sge/renderer/state/alpha_func.hpp>
#include <sge/renderer/state/any.hpp>
#include <sge/renderer/state/any_sort.hpp>
#include <sge/renderer/state/any_sort_functor.hpp>
#include <sge/renderer/state/apply.hpp>
#include <sge/renderer/state/apply_callback.hpp>
#include <sge/renderer/state/bool.hpp>
#include <sge/renderer/state/bool_type.hpp>
#include <sge/renderer/state/color.hpp>
#include <sge/renderer/state/color_type.hpp>
#include <sge/renderer/state/combine.hpp>
#include <sge/renderer/state/cull_mode.hpp>
#include <sge/renderer/state/default.hpp>
#include <sge/renderer/state/depth_func.hpp>
#include <sge/renderer/state/dest_blend_func.hpp>
#include <sge/renderer/state/draw_mode.hpp>
#include <sge/renderer/state/float.hpp>
#include <sge/renderer/state/fog_mode.hpp>
#include <sge/renderer/state/int.hpp>
#include <sge/renderer/state/int_type.hpp>
#include <sge/renderer/state/list.hpp>
#include <sge/renderer/state/list_fwd.hpp>
#include <sge/renderer/state/scoped.hpp>
#include <sge/renderer/state/source_blend_func.hpp>
#include <sge/renderer/state/stack.hpp>
#include <sge/renderer/state/stencil_func.hpp>
#include <sge/renderer/state/stencil_op.hpp>
#include <sge/renderer/state/stencil_op_value.hpp>
#include <sge/renderer/state/to_clear_flags_field.hpp>
#include <sge/renderer/state/trampoline.hpp>
#include <sge/renderer/state/trampoline_fwd.hpp>
#include <sge/renderer/state/uint.hpp>
#include <sge/renderer/state/uint_type.hpp>
#include <sge/renderer/state/var.hpp>
#include <sge/renderer/state/var_fwd.hpp>

#endif
