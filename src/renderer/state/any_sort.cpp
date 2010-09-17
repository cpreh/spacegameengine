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


#include <sge/renderer/state/any_sort.hpp>
#include <sge/renderer/state/var.hpp>
#include <fcppt/variant/apply_binary.hpp>
#include <fcppt/variant/object_impl.hpp>
#include <fcppt/type_info.hpp>
#include <typeinfo>

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
		sge::renderer::state::var<T, States> const &,
		sge::renderer::state::var<T, States> const &
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
	any const &a,
	any const &b
)
{
	return fcppt::variant::apply_binary(
		compare(),
		a,
		b
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
	sge::renderer::state::var<T, States> const &a,
	sge::renderer::state::var<T, States> const &b
) const
{
	return
		a.state()
		< b.state();
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
		fcppt::type_info(
			typeid(T)
		)
		<
		fcppt::type_info(
			typeid(U)
		);
}

}
