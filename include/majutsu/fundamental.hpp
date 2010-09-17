#ifndef MAJUTSU_FUNDAMENTAL_HPP_INCLUDED
#define MAJUTSU_FUNDAMENTAL_HPP_INCLUDED

#include <majutsu/detail/copy_n.hpp>
#include <majutsu/concepts/static_memory/tag.hpp>
#include <majutsu/concepts/static_size.hpp>
#include <majutsu/size_type.hpp>
#include <majutsu/raw_pointer.hpp>
#include <majutsu/integral_size.hpp>
#include <boost/type_traits/is_fundamental.hpp>
#include <boost/static_assert.hpp>

namespace majutsu
{

template<
	typename T
>
struct fundamental {
	typedef T type;

	BOOST_STATIC_ASSERT(
		boost::is_fundamental<T>::value
	);
};

namespace concepts
{

template<
	typename T
>
struct static_size<
	majutsu::fundamental<
		T
	>
>
:
integral_size<
	sizeof(T)
>
{};

}

template<
	typename Type
>
void
place(
	concepts::static_memory::tag const *,
	fundamental<
		Type
	> const *,
	Type const &value_,
	raw_pointer const memory_
)
{
	detail::copy_n(
		reinterpret_cast<
			const_raw_pointer
		>(
			&value_
		),
		concepts::static_size<
			fundamental<
				Type
			>
		>::value,
		memory_
	);
}

template<
	typename Type
>
Type
make(
	concepts::static_memory::tag const *,
	fundamental<
		Type
	> const *,
	const_raw_pointer const memory_
)
{
	Type ret;

	detail::copy_n(
		memory_,
		concepts::static_size<
			fundamental<
				Type
			>
		>::value,
		reinterpret_cast<
			raw_pointer
		>(
			&ret
		)
	);

	return ret;
}

}

#endif
