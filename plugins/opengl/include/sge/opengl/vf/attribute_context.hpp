//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_OPENGL_VF_ATTRIBUTE_CONTEXT_HPP_INCLUDED
#define SGE_OPENGL_VF_ATTRIBUTE_CONTEXT_HPP_INCLUDED

#include <sge/opengl/common.hpp>
#include <sge/opengl/context/base.hpp>
#include <sge/opengl/context/id.hpp>
#include <sge/opengl/info/context_fwd.hpp>
#include <sge/opengl/vf/attribute_context_fwd.hpp>
#include <sge/opengl/vf/optional_attribute_config.hpp>
#include <fcppt/nonmovable.hpp>


namespace sge
{
namespace opengl
{
namespace vf
{

class attribute_context
:
	public sge::opengl::context::base
{
	FCPPT_NONMOVABLE(
		attribute_context
	);
public:
	using
	parameter
	=
	sge::opengl::info::context const &;

	explicit
	attribute_context(
		sge::opengl::info::context const &
	);

	~attribute_context()
	override;

	[[nodiscard]]
	sge::opengl::vf::optional_attribute_config const &
	config() const;

	static sge::opengl::context::id const static_id;
private:
	sge::opengl::vf::optional_attribute_config const config_;
};

}
}
}

#endif
