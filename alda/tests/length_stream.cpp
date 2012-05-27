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
#include <alda/serialization/instantiate_context.hpp>
#include <alda/serialization/instantiate_details.hpp>
#include <alda/serialization/instantiate_message.hpp>
#include <alda/serialization/register_message.hpp>
#include <alda/serialization/length/deserialize.hpp>
#include <alda/serialization/length/put.hpp>
#include <alda/serialization/length/serialize.hpp>
#include <majutsu/composite.hpp>
#include <majutsu/role.hpp>
#include <fcppt/nonassignable.hpp>
#include <fcppt/text.hpp>
#include <fcppt/function/object.hpp>
#include <fcppt/io/cout.hpp>
#include <fcppt/preprocessor/disable_gcc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>
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

struct dispatcher_function
{
	FCPPT_NONASSIGNABLE(
		dispatcher_function
	);
public:
	explicit
	dispatcher_function(
		boost::uint16_t const _value
	)
	:
		value_(
			_value
		)
	{
	}

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
			value_
		);
	}
private:
	boost::uint16_t const value_;
};

}

FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_GCC_WARNING(-Weffc++)

BOOST_AUTO_TEST_CASE(
	alda_length_stream
)
{
FCPPT_PP_POP_WARNING

	std::ostringstream ofs;

	unsigned const count(
		5u
	);

	typedef boost::uint16_t length_type;

	for(
		unsigned index(
			0u
		);
		index < count;
		++index
	)
		alda::serialization::length::serialize<
			length_type
		>(
			ofs,
			*alda::message::make_concrete_ptr<
				type_enum
			>(
				message1(
					static_cast<
						boost::uint16_t
					>(
						index
					)
				)
			)
		);

	std::istringstream ifs;

	ifs.str(
		ofs.str()
	);

	typedef alda::call::object<
		type_enum,
		boost::mpl::vector1<
			message1
		>,
		dispatcher_function
	> dispatcher;

	dispatcher const dispatcher_object;

	for(
		unsigned index(
			0u
		);
		index < count;
		++index
	)
	{
		message_base_unique_ptr result(
			alda::serialization::length::deserialize<
				length_type
			>(
				global_context(),
				ifs
			)
		);

		dispatcher_function fun(
			static_cast<
				boost::uint16_t
			>(
				index
			)
		);

		dispatcher_object(
			*result,
			fun,
			dispatcher::default_function()
		);
	}

	BOOST_CHECK(
		ifs.good()
	);

	ifs.str("");

	{
		message_base_unique_ptr ptr(
			alda::serialization::length::deserialize<
				length_type
			>(
				global_context(),
				ifs
			)
		);

		BOOST_CHECK(
			!ptr
		);
	}

	BOOST_CHECK(
		ifs.good()
	);

	ofs.str("");

	alda::serialization::length::put<
		length_type
	>(
		ofs,
		*alda::message::make_concrete_ptr<
			type_enum
		>(
			message1(
				static_cast<
					boost::uint16_t
				>(
					0
				)
			)
		)
	);

	ifs.str(
		ofs.str()
	);

	{
		message_base_unique_ptr ptr(
			alda::serialization::length::deserialize<
				length_type
			>(
				global_context(),
				ifs
			)
		);

		BOOST_CHECK(
			!ptr
		);
	}

	BOOST_CHECK(
		ifs.good()
	);
}
