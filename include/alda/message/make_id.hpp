#ifndef ALDA_MESSAGE_MAKE_ID_HPP_INCLUDED
#define ALDA_MESSAGE_MAKE_ID_HPP_INCLUDED

#include <alda/bindings/fundamental.hpp>
#include <alda/message/roles/type.hpp>
#include <alda/serialization/detail/message_int_type.hpp>
#include <majutsu/constant.hpp>
#include <majutsu/role.hpp>


namespace alda
{
namespace message
{

template<
	typename EnumType,
	typename EnumType::type MessageType
>
struct make_id
{
	typedef majutsu::role<
		majutsu::constant<
			alda::bindings::fundamental<
				alda::serialization::detail::message_int_type
			>,
			static_cast<
				alda::serialization::detail::message_int_type
			>(
				MessageType
			)
		>,
		alda::message::roles::type
	> type;
};

}
}

#endif
