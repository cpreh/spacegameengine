//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_GUI_IMPL_SPRITE_TYPE_CHOICES_HPP_INCLUDED
#define SGE_GUI_IMPL_SPRITE_TYPE_CHOICES_HPP_INCLUDED

#include <sge/rucksack/scalar.hpp>
#include <sge/sprite/config/float_type.hpp>
#include <sge/sprite/config/type_choices.hpp>
#include <sge/sprite/config/unit_type.hpp>


namespace sge::gui::impl
{

using
sprite_type_choices
=
sge::sprite::config::type_choices<
	sge::sprite::config::unit_type<
		sge::rucksack::scalar
	>,
	sge::sprite::config::float_type<
		float
	>
>;

}

#endif
