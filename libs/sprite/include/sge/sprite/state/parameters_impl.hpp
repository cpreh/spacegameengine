//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_SPRITE_STATE_PARAMETERS_IMPL_HPP_INCLUDED
#define SGE_SPRITE_STATE_PARAMETERS_IMPL_HPP_INCLUDED

#include <sge/sprite/state/parameters_decl.hpp>
#include <sge/sprite/state/detail/parameters_init.hpp>
#include <sge/sprite/state/roles/blend_write_mask.hpp>
#include <sge/sprite/state/roles/enable_scissor_test.hpp>
#include <fcppt/optional/object_impl.hpp>
#include <fcppt/record/init.hpp>
#include <fcppt/record/label_value_type.hpp>
#include <fcppt/record/set.hpp>
#include <fcppt/config/external_begin.hpp>
#include <type_traits>
#include <fcppt/config/external_end.hpp>


template<
	typename StateChoices
>
sge::sprite::state::parameters<
	StateChoices
>::parameters()
:
	elements_(
		fcppt::record::init<
			elements_type
		>(
			sge::sprite::state::detail::parameters_init{}
		)
	)
{
}

template<
	typename StateChoices
>
sge::sprite::state::parameters<
	StateChoices
> &
sge::sprite::state::parameters<
	StateChoices
>::blend_write_mask(
	bool const _blend_write_mask
)
{
	return
		this->set<
			sge::sprite::state::roles::blend_write_mask
		>(
			_blend_write_mask
		);
}

template<
	typename StateChoices
>
sge::sprite::state::parameters<
	StateChoices
> &
sge::sprite::state::parameters<
	StateChoices
>::enable_scissor_test(
	bool const _enable_scissor_test
)
{
	return
		this->set<
			sge::sprite::state::roles::enable_scissor_test
		>(
			_enable_scissor_test
		);
}

template<
	typename StateChoices
>
template<
	typename Role
>
sge::sprite::state::parameters<
	StateChoices
> &
sge::sprite::state::parameters<
	StateChoices
>::set(
	fcppt::record::label_value_type<
		elements_type,
		Role
	> _value
)
{
	return
		fcppt::record::set<
			Role
		>(
			elements_,
			fcppt::optional::object<
				typename
				std::decay<
					fcppt::record::label_value_type<
						elements_type,
						Role
					>
				>::type
			>(
				_value
			)
		);
}

template<
	typename StateChoices
>
typename
sge::sprite::state::parameters<
	StateChoices
>::elements_type const &
sge::sprite::state::parameters<
	StateChoices
>::elements() const
{
	return
		elements_;
}

#endif
