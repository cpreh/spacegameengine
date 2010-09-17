#ifndef MAJUTSU_CONCEPTS_DYNAMIC_MEMORY_MAKE_HPP_INCLUDED
#define MAJUTSU_CONCEPTS_DYNAMIC_MEMORY_MAKE_HPP_INCLUDED

#include <majutsu/raw_pointer.hpp>

namespace majutsu
{
namespace concepts
{
namespace dynamic_memory
{

template<
	typename Element
>
typename Element::type
make(
	const_raw_pointer const place_
)
{
	return
		make(
			static_cast<
				tag const *
			>(0),
			static_cast<
				Element const *
			>(0),
			place_
		);
}

}
}
}

#endif
