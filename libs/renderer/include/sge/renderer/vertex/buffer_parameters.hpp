//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_RENDERER_VERTEX_BUFFER_PARAMETERS_HPP_INCLUDED
#define SGE_RENDERER_VERTEX_BUFFER_PARAMETERS_HPP_INCLUDED

#include <sge/renderer/resource_flags_field.hpp>
#include <sge/renderer/detail/symbol.hpp>
#include <sge/renderer/vertex/buffer_parameters_fwd.hpp>
#include <sge/renderer/vertex/count.hpp>
#include <sge/renderer/vertex/declaration_fwd.hpp>
#include <sge/renderer/vf/dynamic/part_index.hpp>
#include <fcppt/reference_impl.hpp>


namespace sge
{
namespace renderer
{
namespace vertex
{

class buffer_parameters
{
public:
	/**
	\brief Describes a vertex buffer.

	It will be able to hold \a count vertices. \a flags describes the
	capabilities of the buffer. Initially, the contents of the buffer are
	undefined.

	\param declaration The vertex declaration the buffer belongs to

	\param part The part of the vertex declaration the buffer will be
	holding vertices for

	\param count The number of vertices the buffer will hold

	\param flags The capabilitiies of the buffer
	*/
	SGE_RENDERER_DETAIL_SYMBOL
	buffer_parameters(
		sge::renderer::vertex::declaration const &declaration,
		sge::renderer::vf::dynamic::part_index part,
		sge::renderer::vertex::count count,
		sge::renderer::resource_flags_field const &flags
	);

	SGE_RENDERER_DETAIL_SYMBOL
	sge::renderer::vertex::declaration const &
	declaration() const;

	SGE_RENDERER_DETAIL_SYMBOL
	sge::renderer::vf::dynamic::part_index
	part() const;

	SGE_RENDERER_DETAIL_SYMBOL
	sge::renderer::vertex::count
	count() const;

	SGE_RENDERER_DETAIL_SYMBOL
	sge::renderer::resource_flags_field
	flags() const;
private:
	fcppt::reference<
		sge::renderer::vertex::declaration const
	> declaration_;

	sge::renderer::vf::dynamic::part_index part_;

	sge::renderer::vertex::count count_;

	sge::renderer::resource_flags_field flags_;
};

}
}
}

#endif
