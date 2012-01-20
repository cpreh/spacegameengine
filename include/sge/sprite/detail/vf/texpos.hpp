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


#ifndef SGE_SPRITE_DETAIL_VF_TEXPOS_HPP_INCLUDED
#define SGE_SPRITE_DETAIL_VF_TEXPOS_HPP_INCLUDED

#include <sge/renderer/vf/index.hpp>
#include <sge/renderer/vf/texpos.hpp>
#include <sge/sprite/detail/transform_texture_levels_static.hpp>
#include <sge/sprite/detail/config/texture_levels.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/mpl/placeholders.hpp>
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
struct texpos
{
private:
	template<
		typename Level
	>
	struct make_pos
	{
		typedef sge::renderer::vf::texpos<
			typename Choices::type_choices::float_type,
			2,
			sge::renderer::vf::index<
				Level::value
			>
		> type;
	};
public:
	typedef typename sge::sprite::detail::transform_texture_levels_static<
		make_pos<
			boost::mpl::_1
		>,
		typename sge::sprite::detail::config::texture_levels<
			Choices
		>::type
	>::type type;
};

}
}
}
}

#endif
