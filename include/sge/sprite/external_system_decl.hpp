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


#ifndef SGE_SPRITE_EXTERNAL_SYSTEM_DECL_HPP_INCLUDED
#define SGE_SPRITE_EXTERNAL_SYSTEM_DECL_HPP_INCLUDED

#include <sge/sprite/external_system_fwd.hpp>
#include <sge/sprite/object_fwd.hpp>
#include <sge/sprite/system_base_decl.hpp>
#include <sge/renderer/device_fwd.hpp>
#include <fcppt/noncopyable.hpp>

namespace sge
{
namespace sprite
{

template<
	typename Choices
>
class external_system
:
	public sprite::system_base<
		Choices
	>
{
	FCPPT_NONCOPYABLE(
		external_system
	);
public:
	typedef sprite::system_base<
		Choices
	> base;

	typedef sprite::object<
		Choices
	> object;

	explicit external_system(
		renderer::device_ptr
	);

	template<
		typename Iterator,
		typename SortFunction,
		typename EqualFunction
	>
	void
	render(
		Iterator begin,
		Iterator end,
		SortFunction const &,
		EqualFunction const &
	);

	/// doesn't set any matrices or render states!
	template<
		typename Iterator,
		typename SortFunction,
		typename EqualFunction
	>
	void
	render_advanced(
		Iterator begin,
		Iterator end,
		SortFunction const &,
		EqualFunction const &
	);
};

}
}

#endif
