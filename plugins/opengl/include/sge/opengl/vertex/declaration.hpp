//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_OPENGL_VERTEX_DECLARATION_HPP_INCLUDED
#define SGE_OPENGL_VERTEX_DECLARATION_HPP_INCLUDED

#include <sge/opengl/context/object_fwd.hpp>
#include <sge/opengl/vertex/declaration_fwd.hpp>
#include <sge/opengl/vf/part_fwd.hpp>
#include <sge/renderer/vertex/declaration.hpp>
#include <sge/renderer/vertex/declaration_parameters_fwd.hpp>
#include <sge/renderer/vf/dynamic/format.hpp>
#include <sge/renderer/vf/dynamic/part_fwd.hpp>
#include <sge/renderer/vf/dynamic/part_index.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/unique_ptr_impl.hpp>
#include <fcppt/log/object_fwd.hpp>
#include <fcppt/config/external_begin.hpp>
#include <vector>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace opengl
{
namespace vertex
{

class declaration
:
	public sge::renderer::vertex::declaration
{
	FCPPT_NONCOPYABLE(
		declaration
	);
public:
	declaration(
		fcppt::log::object &,
		sge::opengl::context::object &,
		sge::renderer::vertex::declaration_parameters const &
	);

	~declaration()
	override;

	sge::renderer::vf::dynamic::part const &
	format_part(
		sge::renderer::vf::dynamic::part_index
	) const;

	sge::opengl::vf::part const &
	gl_format_part(
		sge::renderer::vf::dynamic::part_index
	) const;
private:
	sge::renderer::vf::dynamic::format const format_;

	// Parts could be movable but lack a proper default state
	typedef
	fcppt::unique_ptr<
		sge::opengl::vf::part
	>
	part_unique_ptr;

	typedef
	std::vector<
		part_unique_ptr
	>
	part_container;

	part_container const parts_;
};

}
}
}

#endif
