#ifndef MAJUTSU_CONCEPTS_DYNAMIC_MEMORY_PLACE_HPP_INCLUDED
#define MAJUTSU_CONCEPTS_DYNAMIC_MEMORY_PLACE_HPP_INCLUDED

#include <majutsu/concepts/dynamic_memory/tag.hpp>
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
void
place(
	typename Element::type const &value_,
	raw_pointer const place_
)
{
	place(
		static_cast<
			tag const *
		>(0),
		static_cast<
			Element const *
		>(0),
		value_,
		place_
	);
}

}
}
}

#endif
