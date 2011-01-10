/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2011 Carl Philipp Reh (sefi@s-e-f-i.de)

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
*/


#ifndef SGE_SPRITE_DETAIL_MAKE_CLASS_HPP_INCLUDED
#define SGE_SPRITE_DETAIL_MAKE_CLASS_HPP_INCLUDED

#include <sge/sprite/with_rotation.hpp>
#include <sge/sprite/with_rotation_center.hpp>
#include <sge/sprite/primitives/pos.hpp>
#include <sge/sprite/primitives/dim.hpp>
#include <sge/sprite/roles/pos.hpp>
#include <fcppt/mpl/implication.hpp>
#include <majutsu/memory/fusion.hpp>
#include <majutsu/class.hpp>
#include <majutsu/role.hpp>
#include <boost/mpl/vector/vector10.hpp>
#include <boost/mpl/apply.hpp>
#include <boost/mpl/transform.hpp>
#include <boost/mpl/placeholders.hpp>
#include <boost/mpl/contains.hpp>
#include <boost/mpl/joint_view.hpp>
#include <boost/static_assert.hpp>

namespace sge
{
namespace sprite
{
namespace detail
{

template<
	typename Choices,
	typename ExtraElements = boost::mpl::vector0<>
>
struct make_class
{
	typedef typename Choices::elements elements;

	BOOST_STATIC_ASSERT((
		fcppt::mpl::implication<
			boost::mpl::contains<
				elements,
				with_rotation_center
			>,
			boost::mpl::contains<
				elements,
				with_rotation
			>
		>::value
	));

	// TODO: why do we need this?
	template<
		typename F,
		typename T1
	>
	struct application
	:
	boost::mpl::apply<
		F,
		T1
	>
	{};

	typedef majutsu::class_<
		typename boost::mpl::joint_view<
			typename boost::mpl::transform<
				elements,
				application<
					boost::mpl::_1,
					Choices
				>
			>::type,
			typename boost::mpl::joint_view<
				boost::mpl::vector1<
					majutsu::role<
						typename primitives::pos<
							typename Choices::type_choices::unit_type
						>::type,
						sge::sprite::roles::pos
					>
				>,
				ExtraElements
			>::type
		>::type,
		majutsu::memory::fusion
	> type;
};

}
}
}

#endif
