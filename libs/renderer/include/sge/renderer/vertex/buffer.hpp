//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_RENDERER_VERTEX_BUFFER_HPP_INCLUDED
#define SGE_RENDERER_VERTEX_BUFFER_HPP_INCLUDED

#include <sge/core/detail/class_symbol.hpp>
#include <sge/renderer/resource_flags_field_fwd.hpp>
#include <sge/renderer/size_type.hpp>
#include <sge/renderer/detail/symbol.hpp>
#include <sge/renderer/vertex/buffer_base.hpp>
#include <sge/renderer/vertex/buffer_fwd.hpp>
#include <sge/renderer/vf/dynamic/part_index.hpp>
#include <fcppt/nonmovable.hpp>


namespace sge::renderer::vertex
{

/**
\brief A buffer for storing parts of vertices

\see sge::renderer::vertex::const_scoped_lock
\see sge::renderer::vertex::scoped_lock
\see sge::renderer::vertex::declaration
\see sge::renderer::device::activate_vertex_buffer
\see sge::renderer::device::craete_vertex_buffer
\see sge::renderer::device::deactivate_vertex_buffer
\see sge::renderer::vf::part
*/
class SGE_CORE_DETAIL_CLASS_SYMBOL buffer
:
	public
		sge::renderer::vertex::buffer_base
{
	FCPPT_NONMOVABLE(
		buffer
	);
protected:
	SGE_RENDERER_DETAIL_SYMBOL
	buffer();
public:
	/**
	\brief Returns the resource flags the buffer has been created with
	*/
	[[nodiscard]]
	virtual
	sge::renderer::resource_flags_field
	resource_flags() const = 0;

	/**
	\brief Returns the index of the vertex format part the buffer
	represents
	*/
	[[nodiscard]]
	virtual
	sge::renderer::vf::dynamic::part_index
	format_part_index() const = 0;

	[[nodiscard]]
	SGE_RENDERER_DETAIL_SYMBOL
	sge::renderer::size_type
	linear_size() const;

	SGE_RENDERER_DETAIL_SYMBOL
	~buffer()
	override;
};

}

#endif
