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
#include <brigand/algorithms/flatten.hpp>
#include <brigand/functions/eval_if.hpp>
#include <brigand/functions/arithmetic/identity.hpp>
#include <brigand/functions/lambda/apply.hpp>
#include <brigand/functions/lambda/bind.hpp>
#include <brigand/sequences/append.hpp>
#include <metal/list/list.hpp>
#include <brigand/types/args.hpp>
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
	brigand::append<
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
	struct make_textures
	{
		typedef
		brigand::append<
			metal::list<
				GeometryTypes
			>,
			sge::sprite::detail::transform_texture_levels_static<
				brigand::bind<
					make_texture_role,
					brigand::_1
				>,
				typename
				sge::sprite::detail::config::texture_levels<
					Choices
				>::type
			>
		>
		type;
	};

public:
	typedef
	fcppt::record::object<
		brigand::flatten<
			typename
			brigand::eval_if<
				sge::sprite::detail::config::has_texture_levels<
					Choices
				>,
				brigand::apply<
					brigand::bind<
						make_textures,
						brigand::pin<
							geometry_types
						>
					>
				>,
				brigand::identity<
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
