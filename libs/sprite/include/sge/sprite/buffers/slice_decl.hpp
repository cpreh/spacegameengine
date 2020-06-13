//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_SPRITE_BUFFERS_SLICE_DECL_HPP_INCLUDED
#define SGE_SPRITE_BUFFERS_SLICE_DECL_HPP_INCLUDED

#include <sge/renderer/index/buffer_fwd.hpp>
#include <sge/renderer/index/first.hpp>
#include <sge/renderer/vertex/buffer_fwd.hpp>
#include <sge/renderer/vertex/first.hpp>
#include <sge/sprite/buffers/object.hpp>
#include <sge/sprite/buffers/offset_object.hpp>
#include <sge/sprite/buffers/slice_fwd.hpp>
#include <fcppt/reference_impl.hpp>


namespace sge
{
namespace sprite
{
namespace buffers
{

template<
	typename Choices
>
class slice
{
public:
	using
	object
	=
	sge::sprite::buffers::object<
		Choices
	>;

	using
	object_ref
	=
	fcppt::reference<
		object const
	>;

	using
	offset_object
	=
	sge::sprite::buffers::offset_object<
		Choices
	>;

	slice(
		object_ref,
		offset_object
	);

	[[nodiscard]]
	sge::renderer::vertex::buffer &
	vertex_buffer() const;

	[[nodiscard]]
	sge::renderer::index::buffer &
	index_buffer() const;

	[[nodiscard]]
	sge::renderer::vertex::first
	first_vertex() const;

	[[nodiscard]]
	sge::renderer::index::first
	first_index() const;

	[[nodiscard]]
	object const &
	buffer_object() const;
private:
	object_ref object_;

	offset_object offsets_;
};

}
}
}

#endif
