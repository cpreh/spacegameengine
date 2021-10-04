//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_OPENGL_VF_PART_HPP_INCLUDED
#define SGE_OPENGL_VF_PART_HPP_INCLUDED

#include <sge/opengl/context/object_ref.hpp>
#include <sge/opengl/vf/actor_fwd.hpp>
#include <sge/opengl/vf/part_fwd.hpp>
#include <sge/opengl/vf/pointer.hpp>
#include <sge/renderer/vf/dynamic/part.hpp>
#include <fcppt/nonmovable.hpp>
#include <fcppt/unique_ptr_impl.hpp>
#include <fcppt/log/object_reference.hpp>
#include <fcppt/config/external_begin.hpp>
#include <vector>
#include <fcppt/config/external_end.hpp>


namespace sge::opengl::vf
{

class part
{
	FCPPT_NONMOVABLE(
		part
	);
public:
	part(
		fcppt::log::object_reference,
		sge::opengl::context::object_ref,
		sge::renderer::vf::dynamic::part &&
	);

	~part();

	[[nodiscard]]
	sge::renderer::vf::dynamic::part const &
	get() const;

	void
	use_me(
		sge::opengl::vf::pointer
	) const;

	void
	unuse_me() const;
private:
	fcppt::log::object_reference const log_;

	sge::opengl::context::object_ref const context_;

	sge::renderer::vf::dynamic::part const part_;

	using
	actor_unique_ptr
	=
	fcppt::unique_ptr<
		sge::opengl::vf::actor
	>;

	using
	actor_container
	=
	std::vector<
		actor_unique_ptr
	>;

	actor_container const actors_;
};

}

#endif
