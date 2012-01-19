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


#ifndef SGE_SPRITE_DETAIL_VF_TEXTURE_POINT_HPP_INCLUDED
#define SGE_SPRITE_DETAIL_VF_TEXTURE_POINT_HPP_INCLUDED

#include <sge/sprite/detail/config/has_custom_texture_point_pos.hpp>
#include <sge/sprite/detail/config/has_custom_texture_point_size.hpp>
#include <sge/sprite/detail/vf/texture_point_pos.hpp>
#include <sge/sprite/detail/vf/texture_point_size.hpp>
#include <fcppt/mpl/append.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/identity.hpp>
#include <boost/mpl/vector/vector10.hpp>
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
struct texture_point
{
private:
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
		sge::sprite::detail::config::has_custom_texture_point_pos<
			Choices
		>,
		make_vector<
			sge::sprite::detail::vf::texture_point_pos<
				Choices
			>
		>,
		boost::mpl::identity<
			boost::mpl::vector0<>
		>
	>::type vec1;

	template<
		typename Type
	>
	struct append_size
	:
	fcppt::mpl::append<
		vec1,
		boost::mpl::vector1<
			typename Type::type
		>
	>
	{
	};
public:
	typedef typename boost::mpl::eval_if<
		sge::sprite::detail::config::has_custom_texture_point_size<
			Choices
		>,
		append_size<
			sge::sprite::detail::vf::texture_point_size<
				Choices
			>
		>,
		boost::mpl::identity<
			vec1
		>
	>::type type;
};

}
}
}
}

#endif
