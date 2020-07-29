//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_OPENGL_VF_POINTER_ACTOR_HPP_INCLUDED
#define SGE_OPENGL_VF_POINTER_ACTOR_HPP_INCLUDED

#include <sge/opengl/vf/actor.hpp>
#include <sge/opengl/vf/actor_parameters_fwd.hpp>
#include <sge/renderer/vf/dynamic/offset.hpp>
#include <sge/renderer/vf/dynamic/stride.hpp>
#include <fcppt/nonmovable.hpp>


namespace sge
{
namespace opengl
{
namespace vf
{

class pointer_actor
:
	public sge::opengl::vf::actor
{
	FCPPT_NONMOVABLE(
		pointer_actor
	);
public:
	~pointer_actor()
	override = 0;
protected:
	explicit
	pointer_actor(
		sge::opengl::vf::actor_parameters const &
	);

	[[nodiscard]]
	sge::renderer::vf::dynamic::offset
	offset() const
	override;

	[[nodiscard]]
	sge::renderer::vf::dynamic::stride
	stride() const;
private:
	sge::renderer::vf::dynamic::offset const offset_;

	sge::renderer::vf::dynamic::stride const stride_;
};

}
}
}

#endif
