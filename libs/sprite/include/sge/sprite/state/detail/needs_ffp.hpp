//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_SPRITE_STATE_DETAIL_NEEDS_FFP_HPP_INCLUDED
#define SGE_SPRITE_STATE_DETAIL_NEEDS_FFP_HPP_INCLUDED

#include <fcppt/config/external_begin.hpp>
#include <metal.hpp>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace sprite
{
namespace state
{
namespace detail
{

template<
	typename StateChoices
>
struct needs_ffp
{
private:
	template<
		typename Type
	>
	using
	extract
	=
	typename
	Type::needs_ffp;
public:
	using
	type
	=
	metal::any_of<
		typename
		StateChoices::optional_elements,
		metal::trait<
			extract
		>
	>;
};

}
}
}
}

#endif
