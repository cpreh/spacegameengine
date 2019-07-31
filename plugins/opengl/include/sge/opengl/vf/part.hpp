//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_OPENGL_VF_PART_HPP_INCLUDED
#define SGE_OPENGL_VF_PART_HPP_INCLUDED

#include <sge/opengl/context/object_fwd.hpp>
#include <sge/opengl/vf/actor_fwd.hpp>
#include <sge/opengl/vf/part_fwd.hpp>
#include <sge/opengl/vf/pointer.hpp>
#include <sge/renderer/vf/dynamic/part.hpp>
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
namespace vf
{

class part
{
	FCPPT_NONCOPYABLE(
		part
	);
public:
	part(
		fcppt::log::object &,
		sge::opengl::context::object &,
		sge::renderer::vf::dynamic::part const &
	);

	~part();

	sge::renderer::vf::dynamic::part const &
	get() const;

	void
	use_me(
		sge::opengl::vf::pointer
	) const;

	void
	unuse_me() const;
private:
	fcppt::log::object &log_;

	sge::opengl::context::object &context_;

	sge::renderer::vf::dynamic::part const part_;

	typedef
	fcppt::unique_ptr<
		sge::opengl::vf::actor
	>
	actor_unique_ptr;

	typedef
	std::vector<
		actor_unique_ptr
	>
	actor_container;

	actor_container const actors_;
};

}
}
}

#endif
