/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2016 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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


#include <sge/plugin/library/function_base_pair.hpp>
#include <sge/plugin/library/detail/make_version_function.hpp>
#include <sge/plugin/library/detail/version_function.hpp>
#include <sge/plugin/impl/library/to_function_base_unsafe.hpp>
#include <sge/plugin/impl/library/version_function_name.hpp>


sge::plugin::library::function_base_pair
sge::plugin::library::detail::make_version_function(
	sge::plugin::library::detail::version_function const _function
)
{
	return
		sge::plugin::library::function_base_pair{
			sge::plugin::impl::library::version_function_name(),
			sge::plugin::impl::library::to_function_base_unsafe(
				_function
			)
		};
}
