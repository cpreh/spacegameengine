//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_PARSE_JSON_DETAIL_IS_ITERABLE_HPP_INCLUDED
#define SGE_PARSE_JSON_DETAIL_IS_ITERABLE_HPP_INCLUDED

#include <fcppt/preprocessor/disable_gcc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>
#include <fcppt/config/external_begin.hpp>
#include <type_traits>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace parse
{
namespace json
{
namespace detail
{

FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_GCC_WARNING(-Weffc++)

template<
	typename Type,
	typename Test = void
>
struct is_iterable
:
std::false_type
{
};

template<
	typename Type
>
struct is_iterable<
	Type,
	decltype(
		std::declval<
			Type
		>().begin()
	)
>
:
std::true_type
{
};

FCPPT_PP_POP_WARNING

}
}
}
}

#endif
