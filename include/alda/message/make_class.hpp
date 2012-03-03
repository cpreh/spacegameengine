#ifndef ALDA_MESSAGE_MAKE_CLASS_HPP_INCLUDED
#define ALDA_MESSAGE_MAKE_CLASS_HPP_INCLUDED

#include <majutsu/memory/raw.hpp>
#include <majutsu/class.hpp>


namespace alda
{
namespace message
{

template<
	typename Message
>
struct make_class
{
	typedef majutsu::class_<
		Message,
		majutsu::memory::raw
	> type;
};

}
}

#endif
