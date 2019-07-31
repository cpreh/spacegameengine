//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_OPENGL_VERTEX_CONTEXT_HPP_INCLUDED
#define SGE_OPENGL_VERTEX_CONTEXT_HPP_INCLUDED

#include <sge/opengl/context/base.hpp>
#include <sge/opengl/context/id.hpp>
#include <sge/opengl/vertex/buffer_fwd.hpp>
#include <sge/opengl/vertex/declaration_fwd.hpp>
#include <sge/renderer/vf/dynamic/part_index.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/container/index_map_decl.hpp>
#include <fcppt/optional/reference.hpp>


namespace sge
{
namespace opengl
{
namespace vertex
{

class context
:
	public sge::opengl::context::base
{
	FCPPT_NONCOPYABLE(
		context
	);
public:
	context();

	~context()
	override;

	typedef
	fcppt::optional::reference<
		sge::opengl::vertex::buffer const
	>
	optional_buffer;

	void
	vertex_buffer(
		sge::renderer::vf::dynamic::part_index,
		optional_buffer
	);

	optional_buffer
	vertex_buffer(
		sge::renderer::vf::dynamic::part_index
	) const;

	typedef
	fcppt::optional::reference<
		sge::opengl::vertex::declaration const
	>
	optional_declaration;

	void
	vertex_declaration(
		optional_declaration
	);

	optional_declaration
	vertex_declaration() const;

	typedef void parameter;

	static sge::opengl::context::id const static_id;
private:
	typedef
	fcppt::container::index_map<
		optional_buffer
	>
	vertex_buffer_map;

	optional_declaration last_declaration_;

	mutable vertex_buffer_map last_buffers_;
};

}
}
}

#endif
