//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_SPRITE_STATE_DETAIL_INIT_ONE_OPTION_HPP_INCLUDED
#define SGE_SPRITE_STATE_DETAIL_INIT_ONE_OPTION_HPP_INCLUDED

#include <fcppt/optional/object_impl.hpp>
#include <fcppt/record/element.hpp>


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
struct init_one_option
{
	template<
		typename Tag
	>
	bool
	operator()(
		fcppt::record::element<
			Tag,
			bool
		>
	) const
	{
		return
			true;
	}

	template<
		typename Type,
		typename Tag
	>
	fcppt::optional::object<
		Type
	>
	operator()(
		fcppt::record::element<
			Tag,
			fcppt::optional::object<
				Type
			>
		>
	) const
	{
		return
			fcppt::optional::object<
				Type
			>();
	}
};

}
}
}
}

#endif
