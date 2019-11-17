//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


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
#include <fcppt/record/element.hpp>
#include <fcppt/record/object_impl.hpp>
#include <fcppt/config/external_begin.hpp>
#include <metal/lambda/always.hpp>
#include <metal/lambda/bind.hpp>
#include <metal/lambda/invoke.hpp>
#include <metal/lambda/lambda.hpp>
#include <metal/list/flatten.hpp>
#include <metal/list/list.hpp>
#include <metal/list/join.hpp>
#include <type_traits>
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
	typedef
	fcppt::record::element<
		sge::sprite::buffers::roles::first_vertex,
		sge::renderer::vertex::first
	>
	first_vertex_role;

	typedef
	fcppt::record::element<
		sge::sprite::buffers::roles::first_index,
		sge::renderer::index::first
	>
	first_index_role;

	typedef
	fcppt::record::element<
		sge::sprite::detail::roles::vertex_count,
		sge::renderer::vertex::count
	>
	vertex_count_role;

	typedef
	fcppt::record::element<
		sge::sprite::detail::roles::index_count,
		sge::renderer::index::count
	>
	index_count_role;

	typedef
	metal::list<
		first_vertex_role,
		vertex_count_role
	>
	base_types;

	typedef
	metal::join<
		base_types,
		metal::list<
			first_index_role,
			index_count_role
		>
	>
	indexed_types;

	typedef
	std::conditional_t<
		sge::sprite::detail::config::needs_index_buffer<
			Choices
		>::value,
		indexed_types,
		base_types
	>
	geometry_types;

	template<
		typename Level
	>
	using
	make_texture_role
	=
	fcppt::record::element<
		sge::sprite::detail::roles::texture<
			Level::value
		>,
		sge::sprite::render::texture_ref
	>;

	template<
		typename GeometryTypes
	>
	using
	make_textures
	=
	metal::join<
		metal::list<
			GeometryTypes
		>,
		sge::sprite::detail::transform_texture_levels_static<
			metal::lambda<
				make_texture_role
			>,
			typename
			sge::sprite::detail::config::texture_levels<
				Choices
			>::type
		>
	>;
public:
	typedef
	fcppt::record::object<
		metal::flatten<
			metal::invoke<
				std::conditional_t<
					sge::sprite::detail::config::has_texture_levels<
						Choices
					>::value,
					metal::bind<
						metal::lambda<
							make_textures
						>,
						metal::always<
							geometry_types
						>
					>,
					metal::always<
						geometry_types
					>
				>
			>
		>
	>
	type;
};

}
}
}
}

#endif
