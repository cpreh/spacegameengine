//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_SPRITE_STATE_OPTIONS_IMPL_HPP_INCLUDED
#define SGE_SPRITE_STATE_OPTIONS_IMPL_HPP_INCLUDED

#include <sge/sprite/optional_projection_dim.hpp>
#include <sge/sprite/projection_dim.hpp>
#include <sge/sprite/state/options_decl.hpp>
#include <sge/sprite/state/vertex_options.hpp>
#include <sge/sprite/state/detail/init_options.hpp>
#include <sge/sprite/state/roles/blend.hpp>
#include <sge/sprite/state/roles/projection_dim.hpp>
#include <sge/sprite/state/roles/rasterizer.hpp>
#include <sge/sprite/state/roles/transform.hpp>
#include <fcppt/record/label_value_type.hpp>
#include <fcppt/record/set.hpp>


template<
	typename StateChoices
>
sge::sprite::state::options<
	StateChoices
>::options(
	sge::sprite::state::vertex_options const _vertex_options
)
:
	vertex_options_(
		_vertex_options
	),
	elements_(
		sge::sprite::state::detail::init_options<
			StateChoices
		>()
	)
{
}

template<
	typename StateChoices
>
sge::sprite::state::options<
	StateChoices
> &
sge::sprite::state::options<
	StateChoices
>::no_blend_state()
{
	return
		this->set<
			sge::sprite::state::roles::blend
		>(
			false
		);
}

template<
	typename StateChoices
>
sge::sprite::state::options<
	StateChoices
> &
sge::sprite::state::options<
	StateChoices
>::no_rasterizer_state()
{
	return
		this->set<
			sge::sprite::state::roles::rasterizer
		>(
			false
		);
}

template<
	typename StateChoices
>
sge::sprite::state::options<
	StateChoices
> &
sge::sprite::state::options<
	StateChoices
>::no_transform_state()
{
	return
		this->set<
			sge::sprite::state::roles::transform
		>(
			false
		);
}

template<
	typename StateChoices
>
sge::sprite::state::options<
	StateChoices
> &
sge::sprite::state::options<
	StateChoices
>::fixed_projection(
	sge::sprite::projection_dim const _projection
)
{
	return
		this->set<
			sge::sprite::state::roles::projection_dim
		>(
			sge::sprite::optional_projection_dim(
				_projection
			)
		);
}

template<
	typename StateChoices
>
sge::sprite::state::vertex_options
sge::sprite::state::options<
	StateChoices
>::vertex_options() const
{
	return
		vertex_options_;
}

template<
	typename StateChoices
>
template<
	typename Role
>
sge::sprite::state::options<
	StateChoices
> &
sge::sprite::state::options<
	StateChoices
>::set(
	fcppt::record::label_value_type<
		elements_type,
		Role
	> _state
)
{
	fcppt::record::set<
		Role
	>(
		elements_,
		_state
	);

	return
		*this;
}

template<
	typename StateChoices
>
typename
sge::sprite::state::options<
	StateChoices
>::elements_type const &
sge::sprite::state::options<
	StateChoices
>::elements() const
{
	return
		elements_;
}

#endif
