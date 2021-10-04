//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_SPRITE_STATE_DETAIL_MAKE_OBJECTS_HPP_INCLUDED
#define SGE_SPRITE_STATE_DETAIL_MAKE_OBJECTS_HPP_INCLUDED

#include <sge/sprite/state/render_device.hpp>
#include <sge/sprite/state/detail/make_one_object.hpp>
#include <sge/sprite/state/detail/object_class.hpp>
#include <sge/sprite/state/detail/parameters_class.hpp>
#include <fcppt/reference_impl.hpp>
#include <fcppt/record/init.hpp>


namespace sge::sprite::state::detail
{

template<
	typename StateChoices
>
inline
sge::sprite::state::detail::object_class<
	StateChoices
>
make_objects(
	fcppt::reference<
		sge::sprite::state::render_device<
			StateChoices
		>
	> const _device,
	sge::sprite::state::detail::parameters_class<
		StateChoices
	> const &_parameters
)
{
	return
		fcppt::record::init<
			sge::sprite::state::detail::object_class<
				StateChoices
			>
		>(
			sge::sprite::state::detail::make_one_object<
				StateChoices
			>(
				_device,
				_parameters
			)
		);
}

}

#endif
