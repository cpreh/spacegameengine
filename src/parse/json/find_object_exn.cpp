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


#include <sge/parse/json/find_object_exn.hpp>
#include <sge/parse/json/path_to_string.hpp>
#include <sge/parse/json/path.hpp>
#include <sge/parse/exception.hpp>
#include <sge/parse/json/get.hpp>
#include <sge/parse/json/object.hpp>
#include <sge/parse/json/member_name_equal.hpp>
#include <sge/parse/json/exception.hpp>
#include <sge/parse/json/array.hpp>
#include <fcppt/type_name.hpp>
#include <fcppt/text.hpp>
#include <algorithm>
#include <typeinfo>

sge::parse::json::object &
sge::parse::json::find_object_exn(
	sge::parse::json::object &input_object,
	json::path const &p)
{
	sge::parse::json::object *current_object = 
		&input_object;

	for(
		json::path::const_iterator current_member = 
			p.begin(); 
		current_member != p.end(); 
		++current_member)
	{
		sge::parse::json::member_vector::iterator it = 
			std::find_if(
				current_object->members.begin(),
				current_object->members.end(),
				sge::parse::json::member_name_equal(
					*current_member));

		if(it == current_object->members.end())
			throw 
				sge::parse::json::exception(
					FCPPT_TEXT("Couldn't navigate to \"")+
					json::path_to_string(
						p)+
					FCPPT_TEXT("\", stopped at \"")+
					(*current_member)+
					FCPPT_TEXT("\" because we couldn't find the object here!"));

		if(it->value.type() != typeid(sge::parse::json::object))
			throw 
				sge::parse::json::exception(
					FCPPT_TEXT("Couldn't navigate to \"")+
					json::path_to_string(
						p)+
					FCPPT_TEXT("\", stopped at \"")+
					(*current_member)+
					FCPPT_TEXT("\" because this member has type \"")+
					fcppt::type_name(
						it->value.type())+
					FCPPT_TEXT("\" instead of type sge::parse::json::object!"));

		current_object = 
			&sge::parse::json::get<sge::parse::json::object>(
				it->value);
	}

	return 
		*current_object;
}

sge::parse::json::object const &
sge::parse::json::find_object_exn(
	sge::parse::json::object const &input_object,
	json::path const &p)
{
	return 
			json::find_object_exn(
				const_cast<sge::parse::json::object &>(
					input_object),
				p);
}
