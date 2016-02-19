/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2016 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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


#ifndef SGE_SPRITE_DETAIL_RENDER_RANGE_PART_OBJECT_HPP_INCLUDED
#define SGE_SPRITE_DETAIL_RENDER_RANGE_PART_OBJECT_HPP_INCLUDED

#include <sge/renderer/index/count.hpp>
#include <sge/renderer/index/first.hpp>
#include <sge/renderer/vertex/count.hpp>
#include <sge/renderer/vertex/first.hpp>
#include <sge/sprite/buffers/roles/first_index.hpp>
#include <sge/sprite/buffers/roles/first_vertex.hpp>
#include <sge/sprite/detail/transform_texture_levels_static.hpp>
#include <sge/sprite/detail/config/has_texture_levels.hpp>
#include <sge/sprite/detail/config/needs_index_buffer.hpp>
#include <sge/sprite/detail/config/texture_levels.hpp>
#include <sge/sprite/detail/roles/index_count.hpp>
#include <sge/sprite/detail/roles/texture.hpp>
#include <sge/sprite/detail/roles/vertex_count.hpp>
#include <sge/sprite/render/texture_ref.hpp>
#include <majutsu/record.hpp>
#include <majutsu/role.hpp>
#include <fcppt/mpl/append.hpp>
#include <fcppt/mpl/flatten.hpp>
#include <fcppt/preprocessor/disable_gcc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/identity.hpp>
#include <boost/mpl/if.hpp>
#include <boost/mpl/vector/vector10.hpp>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace sprite
{
namespace detail
{
namespace render
{

template<
	typename Choices
>
struct range_part_object
{
private:
	typedef majutsu::role<
		sge::renderer::vertex::first,
		sge::sprite::buffers::roles::first_vertex
	> first_vertex_role;

	typedef majutsu::role<
		sge::renderer::index::first,
		sge::sprite::buffers::roles::first_index
	> first_index_role;

	typedef majutsu::role<
		sge::renderer::vertex::count,
		sge::sprite::detail::roles::vertex_count
	> vertex_count_role;

	typedef majutsu::role<
		sge::renderer::index::count,
		sge::sprite::detail::roles::index_count
	> index_count_role;

	typedef boost::mpl::vector2<
		first_vertex_role,
		vertex_count_role
	> base_types;

	typedef typename fcppt::mpl::append<
		base_types,
		boost::mpl::vector2<
			first_index_role,
			index_count_role
		>
	>::type indexed_types;

	typedef typename boost::mpl::if_<
		sge::sprite::detail::config::needs_index_buffer<
			Choices
		>,
		indexed_types,
		base_types
	>::type geometry_types;

	template<
		typename Level
	>
	struct make_texture_role
	{
		typedef majutsu::role<
			sge::sprite::render::texture_ref,
			sge::sprite::detail::roles::texture<
				Level::value
			>
		> type;
	};

FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_GCC_WARNING(-Weffc++)

	template<
		typename GeometryTypes
	>
	struct make_textures
	:
	fcppt::mpl::append<
		boost::mpl::vector1<
			GeometryTypes
		>,
		typename sge::sprite::detail::transform_texture_levels_static<
			make_texture_role<
				boost::mpl::_1
			>,
			typename sge::sprite::detail::config::texture_levels<
				Choices
			>::type
		>::type
	>
	{
	};

FCPPT_PP_POP_WARNING

public:
	typedef
	majutsu::record<
		fcppt::mpl::flatten<
			typename
			boost::mpl::eval_if<
				sge::sprite::detail::config::has_texture_levels<
					Choices
				>,
				make_textures<
					geometry_types
				>,
				boost::mpl::identity<
					geometry_types
				>
			>::type
		>
	>
	type;
};

}
}
}
}

#endif
