//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_SPRITE_RENDER_RANGE_PART_DECL_HPP_INCLUDED
#define SGE_SPRITE_RENDER_RANGE_PART_DECL_HPP_INCLUDED

#include <sge/renderer/index/count.hpp>
#include <sge/renderer/index/first.hpp>
#include <sge/renderer/vertex/count.hpp>
#include <sge/renderer/vertex/first.hpp>
#include <sge/sprite/texture_level.hpp>
#include <sge/sprite/detail/render/range_part_object.hpp>
#include <sge/sprite/render/range_part_fwd.hpp>
#include <sge/sprite/render/texture_ref_fwd.hpp>


namespace sge
{
namespace sprite
{
namespace render
{

template<
	typename Choices
>
class range_part
{
public:
	typedef
	typename
	sge::sprite::detail::render::range_part_object<
		Choices
	>::type
	range_part_object;

	explicit
	range_part(
		range_part_object const &
	);

	sge::renderer::index::first
	first_index() const;

	sge::renderer::vertex::first
	first_vertex() const;

	sge::renderer::vertex::count
	vertex_count() const;

	sge::renderer::index::count
	index_count() const;

	template<
		sge::sprite::texture_level Level
	>
	sge::sprite::render::texture_ref
	texture_level() const;
private:
	range_part_object object_;
};

}
}
}

#endif
