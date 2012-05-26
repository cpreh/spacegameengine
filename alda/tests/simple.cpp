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


#include <alda/exception.hpp>
#include <alda/type_enum.hpp>
#include <alda/bindings/fundamental.hpp>
#include <alda/call/object.hpp>
#include <alda/message/base_decl.hpp>
#include <alda/message/base_unique_ptr.hpp>
#include <alda/message/instantiate_base.hpp>
#include <alda/message/instantiate_concrete.hpp>
#include <alda/message/make_class.hpp>
#include <alda/message/make_id.hpp>
#include <alda/message/make_concrete_ptr.hpp>
#include <alda/serialization/context_fwd.hpp>
#include <alda/serialization/define_context_function.hpp>
#include <alda/serialization/deserialize.hpp>
#include <alda/serialization/instantiate_context.hpp>
#include <alda/serialization/instantiate_details.hpp>
#include <alda/serialization/instantiate_message.hpp>
#include <alda/serialization/register_message.hpp>
#include <alda/serialization/serialize.hpp>
#include <majutsu/composite.hpp>
#include <majutsu/role.hpp>
#include <fcppt/text.hpp>
#include <fcppt/function/object.hpp>
#include <fcppt/io/cerr.hpp>
#include <fcppt/io/cout.hpp>
#include <fcppt/preprocessor/disable_gcc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>
#include <fcppt/tr1/functional.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/cstdint.hpp>
#include <boost/mpl/vector/vector10.hpp>
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

ALDA_MESSAGE_INSTANTIATE_BASE(
	type_enum
);

ALDA_SERIALIZATION_INSTANTIATE_CONTEXT(
	type_enum
);

ALDA_SERIALIZATION_INSTANTIATE_DETAILS(
	type_enum
);

ALDA_MESSAGE_INSTANTIATE_CONCRETE(
	type_enum,
	message1
);

ALDA_SERIALIZATION_INSTANTIATE_MESSAGE(
	type_enum,
	message1
);

ALDA_MESSAGE_INSTANTIATE_CONCRETE(
	type_enum,
	message2
);

ALDA_SERIALIZATION_INSTANTIATE_MESSAGE(
	type_enum,
	message2
);

namespace
{

namespace register1
{

ALDA_SERIALIZATION_REGISTER_MESSAGE(
	global_context(),
	type_enum,
	message1
);

}

namespace register2
{

ALDA_SERIALIZATION_REGISTER_MESSAGE(
	global_context(),
	type_enum,
	message2
);

}

struct dispatcher_function
{
public:
	typedef void result_type;

	result_type
	operator()(
		message1 const &_msg
	) const
	{
		fcppt::io::cout()
			<< FCPPT_TEXT("message1 received\n");

		BOOST_CHECK(
			_msg.get<
				uint16_type
			>()
			==
			static_cast<
				boost::uint16_t
			>(
				1337
			)
		);
	}

	result_type
	operator()(
		message2 const &_msg
	) const
	{
		fcppt::io::cout()
			<< FCPPT_TEXT("message2 received\n");

		BOOST_CHECK(
			_msg.get<
				uint32_type
			>()
			==
			static_cast<
				boost::uint32_t
			>(
				42
			)
		);
	}

	result_type
	default_function(
		message_base const &
	)
	{
	}
};

}

FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_GCC_WARNING(-Weffc++)

BOOST_AUTO_TEST_CASE(
	alda_simple
)
{
FCPPT_PP_POP_WARNING

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

	std::istringstream ifs(
		ofs.str()
	);

	typedef alda::call::object<
		type_enum,
		boost::mpl::vector2<
			message1,
			message2
		>,
		dispatcher_function
	> dispatcher;

	dispatcher const dispatcher_object;

	dispatcher_function receiver;

	dispatcher::default_function const default_callback(
		std::tr1::bind(
			&dispatcher_function::default_function,
			&receiver,
			std::tr1::placeholders::_1
		)
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

		dispatcher_object(
			*result,
			receiver,
			default_callback
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

	ofs.str("");

	alda::serialization::serialize(
		ofs,
		*alda::message::make_concrete_ptr<
			type_enum
		>(
			message2(
				static_cast<
					boost::uint32_t
				>(
					42
				)
			)
		)
	);

	ifs.str(
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
			== message_type::message2
		);

		dispatcher_object(
			*result,
			receiver,
			default_callback
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
