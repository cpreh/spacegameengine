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


#ifndef SGE_RENDERER_STATE_VAR_HPP_INCLUDED
#define SGE_RENDERER_STATE_VAR_HPP_INCLUDED

#include "traits.hpp"
#include "../../export.hpp"

namespace sge
{
namespace renderer
{
namespace state
{

template<typename T>
struct var {
	typedef typename traits<T>::available_states state_type;
	typedef T value_type;

	SGE_SYMBOL var &operator=(
		value_type);
	
	SGE_SYMBOL state_type state() const;
	SGE_SYMBOL value_type value() const;

	SGE_SYMBOL explicit var(
		state_type state,
		value_type defval = value_type());
private:
	state_type state_;
	value_type val_;
};

}
}
}

#endif
