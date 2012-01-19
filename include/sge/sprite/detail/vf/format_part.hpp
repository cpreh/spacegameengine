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


#ifndef SGE_SPRITE_DETAIL_VF_FORMAT_PART_HPP_INCLUDED
#define SGE_SPRITE_DETAIL_VF_FORMAT_PART_HPP_INCLUDED

#include <sge/renderer/vf/part.hpp>
#include <sge/sprite/config/is_point_size.hpp>
#include <sge/sprite/config/is_with_color.hpp>
#include <sge/sprite/config/is_with_texture.hpp>
#include <sge/sprite/config/is_with_texture_point_size.hpp>
#include <sge/sprite/config/normal_size_fwd.hpp>
#include <sge/sprite/detail/vf/color.hpp>
#include <sge/sprite/detail/vf/point_size.hpp>
#include <sge/sprite/detail/vf/pos.hpp>
#include <sge/sprite/detail/vf/texpos.hpp>
#include <sge/sprite/detail/vf/texture_point.hpp>
#include <fcppt/mpl/append.hpp>
#include <fcppt/mpl/contains_if.hpp>
#include <fcppt/mpl/inner.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/fold.hpp>
#include <boost/mpl/identity.hpp>
#include <boost/mpl/pair.hpp>
#include <boost/mpl/placeholders.hpp>
#include <boost/mpl/vector/vector10.hpp>
#include <boost/type_traits/is_same.hpp>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace sprite
{
namespace detail
{
namespace vf
{

template<
	typename Choices
>
struct format_part
{
private:
	typedef boost::mpl::vector1<
		typename sge::sprite::detail::vf::pos<
			Choices
		>::type
	> basic;

	template<
		typename Container
	>
	struct point_size_extra
	:
	fcppt::mpl::append<
		basic,
		boost::mpl::vector1<
			typename sge::sprite::detail::vf::point_size<
				Choices
			>::type
		>
	>
	{
	};

	template<
		typename Type
	>
	struct make_vector
	{
		typedef boost::mpl::vector1<
			typename Type::type
		> type;
	};

	typedef typename boost::mpl::eval_if<
		sge::sprite::config::is_point_size<
			typename Choices::size_choice
		>,
		point_size_extra<
			basic
		>,
		boost::mpl::identity<
			basic
		>
	>::type basic_with_size;

	typedef boost::mpl::vector3<
		boost::mpl::pair<
			sge::sprite::config::is_with_color<
				boost::mpl::_1
			>,
			make_vector<
				sge::sprite::detail::vf::color<
					Choices
				>
			>
		>,
		boost::mpl::pair<
			sge::sprite::config::is_with_texture<
				boost::mpl::_1
			>,
			sge::sprite::detail::vf::texpos<
				Choices
			>
		>,
		boost::mpl::pair<
			sge::sprite::config::is_with_texture_point_size<
				boost::mpl::_1
			>,
			sge::sprite::detail::vf::texture_point<
				Choices
			>
		>
	> optional_primitives;
public:
	typedef sge::renderer::vf::part<
		typename boost::mpl::fold<
			optional_primitives,
			basic_with_size,
			boost::mpl::eval_if<
				fcppt::mpl::contains_if<
					typename Choices::optional_elements,
					boost::mpl::first<
						boost::mpl::_2
					>
				>,
				fcppt::mpl::append<
					boost::mpl::_1,
					fcppt::mpl::inner<
						boost::mpl::second<
							boost::mpl::_2
						>
					>
				>,
				boost::mpl::_1
			>
		>::type
	> type;
};

}
}
}
}

#endif
