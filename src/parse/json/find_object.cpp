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


#include <sge/parse/json/array.hpp>
#include <sge/parse/json/const_optional_object_ref.hpp>
#include <sge/parse/json/exception.hpp>
#include <sge/parse/json/find_member_return_type.hpp>
#include <sge/parse/json/find_member_value.hpp>
#include <sge/parse/json/find_object.hpp>
#include <sge/parse/json/get.hpp>
#include <sge/parse/json/object.hpp>
#include <sge/parse/json/optional_object_ref.hpp>
#include <sge/parse/json/path.hpp>
#include <sge/parse/json/path_to_string.hpp>
#include <fcppt/optional.hpp>
#include <fcppt/text.hpp>
#include <fcppt/type_name.hpp>
#include <fcppt/variant/object_impl.hpp>
#include <fcppt/config/external_begin.hpp>
#include <typeinfo>
#include <fcppt/config/external_end.hpp>

namespace
{

template<
	typename Ret,
	typename Object
>
Ret const
find_object_impl(
	Object &_input_object,
	sge::parse::json::path const &_path)
{
	Ret current_object(
		_input_object);

	for(
		sge::parse::json::path::const_iterator current_member(
			_path.begin());
		current_member != _path.end();
		++current_member)
	{
		typedef typename sge::parse::json::find_member_return_type<
			sge::parse::json::value,
			Object
		>::type optional_value;

		optional_value const val(
			sge::parse::json::find_member_value(
				current_object->members,
				*current_member
			)
		);

		if(!val)
			return Ret();

		if(val->type() != typeid(sge::parse::json::object))
			throw
				sge::parse::json::exception(
					FCPPT_TEXT("Couldn't navigate to \"")+
					sge::parse::json::path_to_string(
						_path)+
					FCPPT_TEXT("\", stopped at \"")+
					(*current_member)+
					FCPPT_TEXT("\" because this member has type \"")+
					fcppt::type_name(
						val->type())+
					FCPPT_TEXT("\" instead of type sge::parse::json::object!"));

		current_object =
			sge::parse::json::get<sge::parse::json::object>(
				*val);
	}

	return
		current_object;
}

}

sge::parse::json::optional_object_ref const
sge::parse::json::find_object(
	sge::parse::json::object &_input_object,
	json::path const &_path)
{
	return
		find_object_impl<
			sge::parse::json::optional_object_ref
		>(
			_input_object,
			_path
		);
}

sge::parse::json::const_optional_object_ref const
sge::parse::json::find_object(
	sge::parse::json::object const &_input_object,
	json::path const &_path)
{
	return
		find_object_impl<
			sge::parse::json::const_optional_object_ref
		>(
			_input_object,
			_path
		);
}
