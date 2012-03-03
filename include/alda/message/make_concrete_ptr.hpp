#ifndef ALDA_MESSAGE_MAKE_CONCRETE_PTR_HPP_INCLUDED
#define ALDA_MESSAGE_MAKE_CONCRETE_PTR_HPP_INCLUDED

#include <alda/message/base_unique_ptr.hpp>
#include <alda/message/concrete_decl.hpp>
#include <fcppt/make_unique_ptr.hpp>


namespace alda
{
namespace message
{

template<
	typename TypeEnum,
	typename Message
>
typename alda::message::base_unique_ptr<
	TypeEnum
>::type
make_concrete_ptr(
	Message const &_value
)
{
	return
		typename alda::message::base_unique_ptr<
			TypeEnum
		>::type(
			fcppt::make_unique_ptr<
				alda::message::concrete<
					TypeEnum,
					Message
				>
			>(
				_value
			)
		);
}

}
}

#endif
