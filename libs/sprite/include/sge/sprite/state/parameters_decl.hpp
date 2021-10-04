//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_SPRITE_STATE_PARAMETERS_DECL_HPP_INCLUDED
#define SGE_SPRITE_STATE_PARAMETERS_DECL_HPP_INCLUDED

#include <sge/sprite/state/parameters_fwd.hpp>
#include <sge/sprite/state/detail/parameters_class.hpp>
#include <fcppt/record/label_value_type.hpp>


namespace sge::sprite::state
{

template<
	typename StateChoices
>
class parameters
{
	using
	elements_type
	=
	sge::sprite::state::detail::parameters_class<
		StateChoices
	>;
public:
	using
	state_choices
	=
	StateChoices;

	parameters();

	parameters &
	blend_write_mask(
		bool
	);

	parameters &
	enable_scissor_test(
		bool
	);

	template<
		typename Role
	>
	parameters &
	set(
		fcppt::record::label_value_type<
			elements_type,
			Role
		>
	);

	[[nodiscard]]
	elements_type const &
	elements() const;
private:
	elements_type elements_;
};

}

#endif
