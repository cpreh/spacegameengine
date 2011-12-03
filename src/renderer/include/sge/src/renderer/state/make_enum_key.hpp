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


#ifndef SGE_SRC_RENDERER_STATE_MAKE_ENUM_KEY_HPP_INCLUDED
#define SGE_SRC_RENDERER_STATE_MAKE_ENUM_KEY_HPP_INCLUDED

#include <sge/renderer/state/alpha_func.hpp>
#include <sge/renderer/state/cull_mode.hpp>
#include <sge/renderer/state/depth_func.hpp>
#include <sge/renderer/state/dest_blend_func.hpp>
#include <sge/renderer/state/draw_mode.hpp>
#include <sge/renderer/state/enum_key.hpp>
#include <sge/renderer/state/fog_mode.hpp>
#include <sge/renderer/state/source_blend_func.hpp>
#include <sge/renderer/state/stencil_func.hpp>


namespace sge
{
namespace renderer
{
namespace state
{

template<
	typename T
>
struct make_enum_key;

#define SGE_RENDERER_STATE_MAKE_ENUM_KEY_INSTANCE(\
	keytype\
)\
template<>\
struct make_enum_key<\
	sge::renderer::state::keytype::type\
>\
{\
	static \
	state::enum_key::type \
	execute() \
	{ \
		return state::enum_key::keytype ;\
	} \
}

SGE_RENDERER_STATE_MAKE_ENUM_KEY_INSTANCE(
	cull_mode
);

SGE_RENDERER_STATE_MAKE_ENUM_KEY_INSTANCE(
	depth_func
);

SGE_RENDERER_STATE_MAKE_ENUM_KEY_INSTANCE(
	stencil_func
);

SGE_RENDERER_STATE_MAKE_ENUM_KEY_INSTANCE(
	alpha_func
);

SGE_RENDERER_STATE_MAKE_ENUM_KEY_INSTANCE(
	fog_mode
);

SGE_RENDERER_STATE_MAKE_ENUM_KEY_INSTANCE(
	draw_mode
);

SGE_RENDERER_STATE_MAKE_ENUM_KEY_INSTANCE(
	source_blend_func
);

SGE_RENDERER_STATE_MAKE_ENUM_KEY_INSTANCE(
	dest_blend_func
);

#undef SGE_RENDERER_STATE_MAKE_ENUM_KEY_INSTANCE

}
}
}

#endif
