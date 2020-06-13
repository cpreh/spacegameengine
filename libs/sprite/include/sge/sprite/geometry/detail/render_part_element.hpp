//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_SPRITE_GEOMETRY_DETAIL_RENDER_PART_ELEMENT_HPP_INCLUDED
#define SGE_SPRITE_GEOMETRY_DETAIL_RENDER_PART_ELEMENT_HPP_INCLUDED

#include <sge/renderer/index/first.hpp>
#include <sge/renderer/texture/planar_fwd.hpp>
#include <sge/renderer/vertex/first.hpp>
#include <sge/sprite/count.hpp>
#include <sge/sprite/deref_texture.hpp>
#include <sge/sprite/object_impl.hpp>
#include <sge/sprite/texture_level.hpp>
#include <sge/sprite/buffers/index_count.hpp>
#include <sge/sprite/buffers/slice_impl.hpp>
#include <sge/sprite/buffers/vertex_count.hpp>
#include <sge/sprite/buffers/roles/first_index.hpp>
#include <sge/sprite/buffers/roles/first_vertex.hpp>
#include <sge/sprite/detail/roles/index_count.hpp>
#include <sge/sprite/detail/roles/texture.hpp>
#include <sge/sprite/detail/roles/vertex_count.hpp>
#include <fcppt/make_cref.hpp>
#include <fcppt/reference_impl.hpp>
#include <fcppt/record/element.hpp>


namespace sge
{
namespace sprite
{
namespace geometry
{
namespace detail
{

template<
	typename Choices
>
class render_part_element
{
public:
	using
	slice_type
	=
	sge::sprite::buffers::slice<
		Choices
	>;

	using
	object_type
	=
	sge::sprite::object<
		Choices
	>;

	render_part_element(
		slice_type const &_slice,
		sge::sprite::count const _offset,
		sge::sprite::count const _count,
		object_type const &_object
	)
	:
		slice_(
			_slice
		),
		offset_(
			_offset
		),
		count_(
			_count
		),
		object_(
			_object
		)
	{
	}

	template<
		typename Type
	>
	Type
	operator()(
		fcppt::record::element<
			sge::sprite::detail::roles::vertex_count,
			Type
		>
	) const
	{
		return
			sge::sprite::buffers::vertex_count<
				Choices
			>(
				count_
			);
	}

	template<
		typename Type
	>
	Type
	operator()(
		fcppt::record::element<
			sge::sprite::buffers::roles::first_vertex,
			Type
		>
	) const
	{
		return
			sge::renderer::vertex::first(
				slice_.get().first_vertex().get()
				+
				sge::sprite::buffers::vertex_count<
					Choices
				>(
					offset_
				).get()
			);
	}

	template<
		typename Type
	>
	Type
	operator()(
		fcppt::record::element<
			sge::sprite::detail::roles::index_count,
			Type
		>
	) const
	{
		return
			sge::sprite::buffers::index_count<
				Choices
			>(
				count_
			);
	}

	template<
		typename Type
	>
	Type
	operator()(
		fcppt::record::element<
			sge::sprite::buffers::roles::first_index,
			Type
		>
	) const
	{
		return
			sge::renderer::index::first(
				slice_.get().first_index().get()
				+
				sge::sprite::buffers::index_count<
					Choices
				>(
					offset_
				).get()
			);
	}

	template<
		typename Type,
		sge::sprite::texture_level Level
	>
	Type
	operator()(
		fcppt::record::element<
			sge::sprite::detail::roles::texture<
				Level
			>,
			Type
		>
	) const
	{
		return
			fcppt::make_cref(
				sge::sprite::deref_texture(
					object_.get(). template texture_level<
						Level
					>()
				).texture()
			);
	}
private:
	fcppt::reference<
		slice_type const
	> slice_;

	sge::sprite::count offset_;

	sge::sprite::count count_;

	fcppt::reference<
		object_type const
	> object_;
};

}
}
}
}

#endif
