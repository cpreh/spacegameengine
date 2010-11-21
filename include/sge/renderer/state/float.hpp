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


#ifndef SGE_RENDERER_STATE_FLOAT_HPP_INCLUDED
#define SGE_RENDERER_STATE_FLOAT_HPP_INCLUDED

#include <sge/renderer/scalar.hpp>
#include <sge/renderer/state/trampoline_fwd.hpp>
#include <sge/renderer/state/var_fwd.hpp>
#include <sge/symbol.hpp>

namespace sge
{
namespace renderer
{
namespace state
{

namespace float_ {
	typedef scalar base_type;

	namespace available_states {
		enum type {
			zbuffer_clear_val,
			alpha_test_ref,
			fog_start,
			fog_end,
			fog_density
		};
	}

	typedef trampoline<
		base_type,
		available_states::type
	> trampoline_type;

	typedef var<
		base_type,
		available_states::type
	> type;

	SGE_SYMBOL extern trampoline_type const
		zbuffer_clear_val,
		alpha_test_ref,
		fog_start,
		fog_end,
		fog_density;
}

}
}
}

#endif
