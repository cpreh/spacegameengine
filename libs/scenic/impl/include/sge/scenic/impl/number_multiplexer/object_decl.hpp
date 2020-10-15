//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_SCENIC_IMPL_NUMBER_MULTIPLEXER_OBJECT_DECL_HPP_INCLUDED
#define SGE_SCENIC_IMPL_NUMBER_MULTIPLEXER_OBJECT_DECL_HPP_INCLUDED

#include <sge/scenic/impl/number_multiplexer/object_fwd.hpp>
#include <fcppt/make_strong_typedef.hpp>
#include <fcppt/strong_typedef.hpp>
#include <fcppt/config/external_begin.hpp>
#include <type_traits>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace scenic
{
namespace impl
{
namespace number_multiplexer
{

template<
	typename T
>
class object
{
	static_assert(
		std::is_unsigned_v<T>,
		"number_multiplexer only works on unsigned types"
	);
public:
	using
	value_type
	=
	T;

	FCPPT_MAKE_STRONG_TYPEDEF(
		value_type,
		bit_count
	);

	object();

	explicit
	object(
		value_type
	);

	object &
	append(
		bit_count const &,
		value_type
	);

	[[nodiscard]]
	value_type
	value() const;
private:
	value_type value_;
	value_type last_bit_set_;
};

}
}
}
}

#endif
