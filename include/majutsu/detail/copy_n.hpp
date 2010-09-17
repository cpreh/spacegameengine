#ifndef MAJUTSU_DETAIL_COPY_N_HPP_INCLUDED
#define MAJUTSU_DETAIL_COPY_N_HPP_INCLUDED

#include <majutsu/raw_pointer.hpp>
#include <majutsu/size_type.hpp>
#include <cstring>

namespace majutsu
{
namespace detail
{

inline void
copy_n(
	const_raw_pointer const src,
	size_type const sz,
	raw_pointer const dest
)
{
	std::memcpy(
		dest,
		src,
		sz
	);
}

}
}

#endif
