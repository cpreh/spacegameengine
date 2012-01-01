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


#include <sge/renderer/state/any_key.hpp>
#include <sge/renderer/state/any_key_types.hpp>
#include <sge/renderer/state/any_sort.hpp>
#include <fcppt/mpl/index_of.hpp>
#include <fcppt/variant/apply_binary.hpp>
#include <fcppt/variant/object_impl.hpp>


namespace
{

class compare
{
public:
	typedef bool result_type;

	template<
		typename T
	>
	result_type
	operator()(
		T,
		T
	) const;

	template<
		typename T,
		typename U
	>
	result_type
	operator()(
		T,
		U
	) const;
};

}

bool
sge::renderer::state::any_sort(
	state::any_key const &_left,
	state::any_key const &_right
)
{
	return
		fcppt::variant::apply_binary(
			compare(),
			_left,
			_right
		);
}

namespace
{

template<
	typename T
>
bool
compare::operator()(
	T const _key1,
	T const _key2
) const
{
	return
		_key1
		< _key2;
}

template<
	typename T,
	typename U
>
bool
compare::operator()(
	T,
	U
) const
{
	return
		fcppt::mpl::index_of<
			sge::renderer::state::any_key_types,
			T
		>::value
		<
		fcppt::mpl::index_of<
			sge::renderer::state::any_key_types,
			U
		>::value;
}

}
