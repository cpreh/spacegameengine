#ifndef MAJUTSU_CONCEPTS_DYNAMIC_MEMORY_NEEDED_SIZE_HPP_INCLUDED
#define MAJUTSU_CONCEPTS_DYNAMIC_MEMORY_NEEDED_SIZE_HPP_INCLUDED

#include <majutsu/concepts/static_size.hpp>
#include <majutsu/size_type.hpp>

namespace majutsu
{
namespace concepts
{
namespace dynamic_memory
{

template<
	typename Element
>
size_type
needed_size(
	typename Element::type const &value_
)
{
	return
		needed_size(
			static_cast<
				tag const *
			>(0),
			static_cast<
				Element const *
			>(0),
			value_
		);
}

template<
	typename Element
>
typename concepts::static_size<
	Element
>::value_type
needed_size(
	tag const *,
	Element const *,
	typename Element::type const &
)
{
	return static_size<Element>::value; 
}

}
}
}

#endif
