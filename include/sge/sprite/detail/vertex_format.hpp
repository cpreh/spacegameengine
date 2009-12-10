/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2009 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#ifndef SGE_SPRITE_DETAIL_VERTEX_FORMAT_HPP_INCLUDED
#define SGE_SPRITE_DETAIL_VERTEX_FORMAT_HPP_INCLUDED

#include <sge/sprite/detail/vertex_pos.hpp>
#include <sge/sprite/detail/vertex_texpos.hpp>
#include <sge/sprite/detail/vertex_color.hpp>
#include <sge/sprite/with_color.hpp>
#include <sge/sprite/with_texture.hpp>
#include <sge/renderer/vf/format.hpp>
#include <sge/mpl/inner.hpp>
#include <boost/mpl/vector/vector10.hpp>
#include <boost/mpl/pair.hpp>
#include <boost/mpl/contains.hpp>
#include <boost/mpl/fold.hpp>
#include <boost/mpl/placeholders.hpp>
#include <boost/mpl/push_back.hpp>
#include <boost/mpl/eval_if.hpp>

namespace sge
{
namespace sprite
{
namespace detail
{

template<
	typename Choices
>
struct vertex_format
{
private:
	typedef typename Choices::type_choices type_choices;

	typedef boost::mpl::vector1<
		typename vertex_pos<
			type_choices
		>::type
	> basic;

	typedef boost::mpl::vector2<
		boost::mpl::pair<
			with_color,
			vertex_color<
				type_choices
			>
		>,
		boost::mpl::pair<
			with_texture,
			vertex_texpos<
				type_choices
			>
		>
	> optional_elements;
public:
	typedef renderer::vf::format<
		typename boost::mpl::fold<
			optional_elements,
			basic,
			boost::mpl::eval_if<
				boost::mpl::contains<
					typename Choices::elements,
					boost::mpl::first<
						boost::mpl::_2
					>
				>,
				boost::mpl::push_back<
					boost::mpl::_1,
					sge::mpl::inner<
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

#endif
