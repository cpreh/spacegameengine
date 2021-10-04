//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_OPENGL_VERTEX_DECLARATION_HPP_INCLUDED
#define SGE_OPENGL_VERTEX_DECLARATION_HPP_INCLUDED

#include <sge/opengl/context/object_ref.hpp>
#include <sge/opengl/vertex/declaration_fwd.hpp>
#include <sge/opengl/vf/part_fwd.hpp>
#include <sge/renderer/vertex/declaration.hpp>
#include <sge/renderer/vertex/declaration_parameters_fwd.hpp>
#include <sge/renderer/vf/dynamic/format.hpp>
#include <sge/renderer/vf/dynamic/part_fwd.hpp>
#include <sge/renderer/vf/dynamic/part_index.hpp>
#include <fcppt/nonmovable.hpp>
#include <fcppt/unique_ptr_impl.hpp>
#include <fcppt/log/object_reference.hpp>
#include <fcppt/config/external_begin.hpp>
#include <vector>
#include <fcppt/config/external_end.hpp>


namespace sge::opengl::vertex
{

class declaration
:
	public sge::renderer::vertex::declaration
{
	FCPPT_NONMOVABLE(
		declaration
	);
public:
	declaration(
		fcppt::log::object_reference,
		sge::opengl::context::object_ref,
		sge::renderer::vertex::declaration_parameters const &
	);

	~declaration()
	override;

	[[nodiscard]]
	sge::renderer::vf::dynamic::part const &
	format_part(
		sge::renderer::vf::dynamic::part_index
	) const;

	[[nodiscard]]
	sge::opengl::vf::part const &
	gl_format_part(
		sge::renderer::vf::dynamic::part_index
	) const;
private:
	sge::renderer::vf::dynamic::format const format_;

	// Parts could be movable but lack a proper default state
	using
	part_unique_ptr
	=
	fcppt::unique_ptr<
		sge::opengl::vf::part
	>;

	using
	part_container
	=
	std::vector<
		part_unique_ptr
	>;

	part_container const parts_;
};

}

#endif
