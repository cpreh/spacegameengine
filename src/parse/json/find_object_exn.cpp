/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2015 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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


#include <sge/parse/exception.hpp>
#include <sge/parse/json/array.hpp>
#include <sge/parse/json/find_object.hpp>
#include <sge/parse/json/find_object_exn.hpp>
#include <sge/parse/json/object.hpp>
#include <sge/parse/json/path.hpp>
#include <sge/parse/json/path_to_string.hpp>
#include <fcppt/optional/to_exception.hpp>
#include <fcppt/text.hpp>


namespace
{

template<
	typename Object
>
Object &
find_object_exn_impl(
	Object &_input_object,
	sge::parse::json::path const &_path
)
{
	return
		fcppt::optional::to_exception(
			sge::parse::json::find_object(
				_input_object,
				_path
			),
			[
				&_path
			]{
				return
					sge::parse::exception(
						FCPPT_TEXT("Couldn't navigate to \"")
						+
						sge::parse::json::path_to_string(
							_path
						)
						+
						FCPPT_TEXT("\" because we couldn't find the object here!")
					);
			}
		);
}

}

sge::parse::json::object &
sge::parse::json::find_object_exn(
	sge::parse::json::object &_input_object,
	sge::parse::json::path const &_path
)
{
	return
		find_object_exn_impl(
			_input_object,
			_path
		);
}

sge::parse::json::object const &
sge::parse::json::find_object_exn(
	sge::parse::json::object const &_input_object,
	sge::parse::json::path const &_path
)
{
	return
		find_object_exn_impl(
			_input_object,
			_path
		);
}
