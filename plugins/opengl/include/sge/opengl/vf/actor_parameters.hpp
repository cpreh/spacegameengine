//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_OPENGL_VF_ACTOR_PARAMETERS_HPP_INCLUDED
#define SGE_OPENGL_VF_ACTOR_PARAMETERS_HPP_INCLUDED

#include <sge/opengl/context/object_fwd.hpp>
#include <sge/opengl/vf/actor_parameters_fwd.hpp>
#include <sge/renderer/vf/dynamic/offset.hpp>
#include <sge/renderer/vf/dynamic/stride.hpp>
#include <fcppt/reference_impl.hpp>


namespace sge
{
namespace opengl
{
namespace vf
{

class actor_parameters
{
public:
	actor_parameters(
		sge::renderer::vf::dynamic::stride,
		sge::renderer::vf::dynamic::offset,
		sge::opengl::context::object &
	);

	sge::renderer::vf::dynamic::stride
	stride() const;

	sge::renderer::vf::dynamic::offset
	offset() const;

	sge::opengl::context::object &
	context() const;
private:
	sge::renderer::vf::dynamic::stride stride_;

	sge::renderer::vf::dynamic::offset offset_;

	fcppt::reference<
		sge::opengl::context::object
	> context_;
};

}
}
}

#endif
