/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2012 Carl Philipp Reh (sefi@s-e-f-i.de)

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

#include <sge/sprite/vector.hpp>
#include <sge/sprite/roles/pos.hpp>
#include <majutsu/class.hpp>
#include <majutsu/role.hpp>
#include <majutsu/simple.hpp>
#include <majutsu/memory/fusion.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/mpl/apply.hpp>
#include <boost/mpl/joint_view.hpp>
#include <boost/mpl/placeholders.hpp>
#include <boost/mpl/transform.hpp>
#include <boost/mpl/vector/vector10.hpp>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace sprite
{
namespace detail
{

template<
	typename Choices,
	typename ExtraElements
>
struct make_class
{
private:
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
public:
	typedef majutsu::class_<
		typename boost::mpl::joint_view<
			typename boost::mpl::transform<
				typename Choices::optional_elements,
				application<
					boost::mpl::_1,
					Choices
				>
			>::type,
			boost::mpl::joint_view<
				boost::mpl::vector2<
					majutsu::role<
						majutsu::simple<
							typename sge::sprite::vector<
								Choices
							>::type
						>,
						sge::sprite::roles::pos
					>,
					typename boost::mpl::apply<
						typename Choices::size_choice,
						Choices
					>::type
				>,
				ExtraElements
			>
		>::type,
		majutsu::memory::fusion
	> type;
};

}
}
}

#endif
