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


#ifndef SGE_RENDERER_STATE_ANY_KEY_TYPES_HPP_INCLUDED
#define SGE_RENDERER_STATE_ANY_KEY_TYPES_HPP_INCLUDED

#include <sge/renderer/state/bool.hpp>
#include <sge/renderer/state/color.hpp>
#include <sge/renderer/state/enum_key.hpp>
#include <sge/renderer/state/float.hpp>
#include <sge/renderer/state/int.hpp>
#include <sge/renderer/state/stencil_op.hpp>
#include <sge/renderer/state/uint.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/mpl/vector/vector10.hpp>
#include <fcppt/config/external_end.hpp>

namespace sge
{
namespace renderer
{
namespace state
{

typedef
boost::mpl::vector7<
	state::int_::available_states::type,
	state::uint::available_states::type,
	state::float_::available_states::type,
	state::bool_::available_states::type,
	state::color::available_states::type,
	stencil_op::available_states::type,
	state::enum_key::type
> any_key_types;

}
}
}

#endif
