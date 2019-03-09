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


#ifndef SGE_PARSE_JSON_GET_EXN_MESSAGE_HPP_INCLUDED
#define SGE_PARSE_JSON_GET_EXN_MESSAGE_HPP_INCLUDED

#include <sge/parse/json/invalid_get.hpp>
#include <sge/parse/json/value.hpp>
#include <sge/parse/json/detail/get_return_type.hpp>
#include <fcppt/from_std_string.hpp>
#include <fcppt/text.hpp>
#include <fcppt/type_name_from_info.hpp>
#include <fcppt/optional/to_exception.hpp>
#include <fcppt/variant/to_optional_ref.hpp>
#include <fcppt/variant/type_info.hpp>
#include <fcppt/config/external_begin.hpp>
#include <type_traits>
#include <typeinfo>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace parse
{
namespace json
{

template<
	typename Type,
	typename Arg,
	typename MakeMessage
>
sge::parse::json::detail::get_return_type<
	Type,
	Arg
>
get_exn_message(
	Arg &_val,
	MakeMessage const &_make_message
)
{
	static_assert(
		std::is_same_v<
			std::remove_const_t<
				Arg
			>,
			sge::parse::json::value
		>
	);

	return
		fcppt::optional::to_exception(
			fcppt::variant::to_optional_ref<
				std::conditional_t<
					std::is_const_v<
						Arg
					>,
					Type const,
					Type
				>
			>(
				_val.get()
			),
			[
				&_val,
				&_make_message
			]{
				return
					sge::parse::json::invalid_get(
						FCPPT_TEXT("json::get_exn<")
						+
						fcppt::from_std_string(
							fcppt::type_name_from_info(
								typeid(
									Type
								)
							)
						)
						+
						FCPPT_TEXT("> failed! Type is \"")
						+
						fcppt::from_std_string(
							fcppt::type_name_from_info(
								fcppt::variant::type_info(
									_val.get()
								)
							)
						)
						+
						FCPPT_TEXT("\" instead! Additional information: ")
						+
						_make_message()
					);
			}
		).get();
}

}
}
}

#endif
