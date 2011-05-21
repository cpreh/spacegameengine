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


#ifndef SGE_RENDERER_STATE_ANY_HPP_INCLUDED
#define SGE_RENDERER_STATE_ANY_HPP_INCLUDED

#include <sge/renderer/state/int.hpp>
#include <sge/renderer/state/uint.hpp>
#include <sge/renderer/state/float.hpp>
#include <sge/renderer/state/bool.hpp>
#include <sge/renderer/state/color.hpp>
#include <sge/renderer/state/cull_mode.hpp>
#include <sge/renderer/state/depth_func.hpp>
#include <sge/renderer/state/stencil_func.hpp>
#include <sge/renderer/state/alpha_func.hpp>
#include <sge/renderer/state/fog_mode.hpp>
#include <sge/renderer/state/draw_mode.hpp>
#include <sge/renderer/state/source_blend_func.hpp>
#include <sge/renderer/state/dest_blend_func.hpp>
#include <sge/renderer/state/stencil_op.hpp>
#include <sge/renderer/state/var.hpp>
#include <fcppt/variant/object_fwd.hpp>
#include <boost/mpl/vector/vector20.hpp>

namespace sge
{
namespace renderer
{
namespace state
{

typedef fcppt::variant::object<
	boost::mpl::vector14<
		int_::type,
		uint::type,
		float_::type,
		bool_::type,
		color::type,
		cull_mode::type,
		depth_func::type,
		stencil_func::type,
		alpha_func::type,
		fog_mode::type,
		draw_mode::type,
		source_blend_func::type,
		dest_blend_func::type,
		stencil_op::type
	>
> any;

}
}
}

#endif
