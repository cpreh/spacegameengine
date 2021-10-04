//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_SCENIC_IMPL_NUMBER_MULTIPLEXER_SET_BITS_HPP_INCLUDED
#define SGE_SCENIC_IMPL_NUMBER_MULTIPLEXER_SET_BITS_HPP_INCLUDED

namespace sge::scenic::impl::number_multiplexer
{
template<typename T>
T
set_bits(
	T const begin,
	T const size,
	T const value,
	T const input)
{
	T const one{
		1U
	};

	T const part =
		((one << begin) - one) ^ ((one << (begin + size)) - one);

	return
		(input & ~part) | (value << begin);
}

}

#endif
