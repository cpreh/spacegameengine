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


#include <sge/renderer/state/any_key.hpp>
#include <sge/renderer/state/any_key_types.hpp>
#include <sge/renderer/state/any_sort.hpp>
#include <sge/renderer/state/enum_key.hpp>
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
		typename T,
		typename States
	>
	result_type
	operator()(
		sge::renderer::state::enum_key::type,
		sge::renderer::state::enum_key::type
	) const;

	template<
		typename T,
		typename U
	>
	result_type
	operator()(
		T const &,
		U const &
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
	typename T,
	typename States
>
bool
compare::operator()(
	sge::renderer::state::enum_key::type const _key1,
	sge::renderer::state::enum_key::type const _key2
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
	T const &,
	U const &
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
