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


#include <sge/renderer/state/any.hpp>
#include <sge/renderer/state/any_key.hpp>
#include <sge/renderer/state/var.hpp>
#include <sge/src/renderer/state/make_enum_key.hpp>
#include <sge/src/renderer/state/make_key.hpp>
#include <sge/src/renderer/state/make_state_key.hpp>
#include <fcppt/variant/apply_unary.hpp>
#include <fcppt/variant/object_impl.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/type_traits/is_enum.hpp>
#include <boost/utility/enable_if.hpp>
#include <fcppt/config/external_end.hpp>

namespace
{

struct key_visitor
{
	typedef sge::renderer::state::any_key result_type;

	template<
		typename Type
	>
	typename boost::enable_if<
		boost::is_enum<
			Type
		>,
		result_type
	>::type const
	operator()(
		Type
	) const
	{
		return
			sge::renderer::state::make_enum_key<
				Type
			>::execute();
	}

	template<
		typename Type,
		typename States
	>
	result_type const
	operator()(
		sge::renderer::state::var<
			Type,
			States
		> const &_var
	) const
	{
		return
			sge::renderer::state::make_state_key(
				_var.state()
			);
	}
};

}

sge::renderer::state::any_key const
sge::renderer::state::make_key(
	state::any const &_arg
)
{
	return
		fcppt::variant::apply_unary(
			::key_visitor(),
			_arg
		);
}
