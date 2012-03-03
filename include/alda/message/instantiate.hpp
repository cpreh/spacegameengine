#ifndef ALDA_MESSAGE_INSTANTIATE_HPP_INCLUDED
#define ALDA_MESSAGE_INSTANTIATE_HPP_INCLUDED

#include <alda/message/instantiate_concrete.hpp>
#include <alda/serialization/detail/register_class.hpp>
#include <alda/serialization/instantiate_message.hpp>


#define ALDA_MESSAGE_INSTANTIATE(\
	visibility_macro,\
	context,\
	type_enum,\
	msg\
) \
ALDA_SERIALIZATION_DETAIL_REGISTER_CLASS(\
	context,\
	type_enum,\
	msg\
)\
ALDA_SERIALIZATION_INSTANTIATE_MESSAGE(\
	visibility_macro,\
	type_enum,\
	msg\
); \
ALDA_MESSAGE_INSTANTIATE_CONCRETE(\
	visibility_macro,\
	type_enum,\
	msg\
)

#endif
