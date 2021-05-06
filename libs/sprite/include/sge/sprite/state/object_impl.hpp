//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_SPRITE_STATE_OBJECT_IMPL_HPP_INCLUDED
#define SGE_SPRITE_STATE_OBJECT_IMPL_HPP_INCLUDED

#include <sge/sprite/state/object_decl.hpp>
#include <sge/sprite/state/parameters_impl.hpp>
#include <sge/sprite/state/detail/make_objects.hpp>
#include <fcppt/reference_impl.hpp>


template<
	typename StateChoices
>
sge::sprite::state::object<
	StateChoices
>::object(
	fcppt::reference<
		render_device
	> const _renderer,
	parameters_type const &_parameters
)
:
	renderer_(
		_renderer
	),
	elements_(
		sge::sprite::state::detail::make_objects<
			StateChoices
		>(
			_renderer,
			_parameters.elements()
		)
	)
{
}

namespace sge::sprite::state
{
template<
	typename StateChoices
>
object<
	StateChoices
>::~object()
= default;
}

template<
	typename StateChoices
>
typename
sge::sprite::state::object<
	StateChoices
>::elements_type &
sge::sprite::state::object<
	StateChoices
>::elements()
{
	return
		elements_;
}

template<
	typename StateChoices
>
typename
sge::sprite::state::object<
	StateChoices
>::elements_type const &
sge::sprite::state::object<
	StateChoices
>::elements() const
{
	return
		elements_;
}

template<
	typename StateChoices
>
typename
sge::sprite::state::object<
	StateChoices
>::render_device &
sge::sprite::state::object<
	StateChoices
>::renderer() const
{
	return
		renderer_.get();
}

#endif
