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


#include <alda/exception_impl.hpp>
#include <alda/type_enum.hpp>
#include <alda/bindings/fundamental.hpp>
#include <alda/message/base_decl.hpp>
#include <alda/message/base_unique_ptr.hpp>
#include <alda/message/instantiate.hpp>
#include <alda/message/instantiate_base.hpp>
#include <alda/message/make_class.hpp>
#include <alda/message/make_id.hpp>
#include <alda/message/make_concrete_ptr.hpp>
#include <alda/serialization/define_context_function.hpp>
#include <alda/serialization/deserialize.hpp>
#include <alda/serialization/instantiate_details.hpp>
#include <alda/serialization/instantiate_context.hpp>
#include <alda/serialization/serialize.hpp>
#include <majutsu/composite.hpp>
#include <majutsu/role.hpp>
#include <fcppt/text.hpp>
#include <fcppt/io/cerr.hpp>
#include <fcppt/io/cout.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/cstdint.hpp>
#include <boost/mpl/vector/vector10.hpp>
#include <boost/preprocessor/empty.hpp>
#include <boost/test/unit_test.hpp>
#include <sstream>
#include <fcppt/config/external_end.hpp>


namespace
{

namespace message_type
{
enum type
{
	message1,
	message2,
	size
};
}

typedef alda::type_enum<
	message_type::type,
	message_type::size
> type_enum;


typedef alda::message::base<
	type_enum
> message_base;

typedef alda::message::base_unique_ptr<
	type_enum
>::type message_base_unique_ptr;

typedef alda::bindings::fundamental<
	boost::uint16_t
> uint16_type;

typedef alda::bindings::fundamental<
	boost::uint32_t
> uint32_type;

typedef alda::message::make_class<
	majutsu::composite<
		boost::mpl::vector2<
			alda::message::make_id<
				type_enum,
				message_type::message1
			>::type,
			majutsu::role<
				uint16_type
			>
		>
	>
>::type message1;

typedef alda::message::make_class<
	majutsu::composite<
		boost::mpl::vector2<
			alda::message::make_id<
				type_enum,
				message_type::message2
			>::type,
			majutsu::role<
				uint32_type
			>
		>
	>
>::type message2;

typedef alda::serialization::context<
	type_enum
> context;

context &
global_context();

ALDA_SERIALIZATION_DEFINE_CONTEXT_FUNCTION(
	type_enum,
	global_context
)

}

#define VISIBILITY BOOST_PP_EMPTY

ALDA_MESSAGE_INSTANTIATE_BASE(
	VISIBILITY,
	type_enum
);

ALDA_SERIALIZATION_INSTANTIATE_CONTEXT(
	VISIBILITY,
	type_enum
);

ALDA_SERIALIZATION_INSTANTIATE_DETAILS(
	VISIBILITY,
	type_enum
);

ALDA_MESSAGE_INSTANTIATE(
	VISIBILITY,
	global_context(),
	type_enum,
	message1
);

/*
ALDA_MESSAGE_INSTANTIATE(
	VISIBILITY,
	global_context(),
	type_enum,
	message2
);
*/

BOOST_AUTO_TEST_CASE(
	alda_simple
)
{
	std::ostringstream ofs;

	alda::serialization::serialize(
		ofs,
		*alda::message::make_concrete_ptr<
			type_enum
		>(
			message1(
				static_cast<
					boost::uint16_t
				>(
					1337
				)
			)
		)
	);

	fcppt::io::cout()
		<< ofs.str().size()
		<< FCPPT_TEXT(" bytes written\n");

	std::istringstream ifs(
		ofs.str()
	);

	try
	{
		message_base_unique_ptr result(
			alda::serialization::deserialize(
				global_context(),
				ifs
			)
		);

		BOOST_CHECK(
			result->type()
			== message_type::message1
		);
	}
	catch(
		alda::exception const &_exception
	)
	{
		fcppt::io::cerr()
			<< _exception.string()
			<< FCPPT_TEXT('\n');
	}
}
