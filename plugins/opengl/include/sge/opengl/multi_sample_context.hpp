//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_OPENGL_MULTI_SAMPLE_CONTEXT_HPP_INCLUDED
#define SGE_OPENGL_MULTI_SAMPLE_CONTEXT_HPP_INCLUDED

#include <sge/opengl/multi_sample_context_fwd.hpp>
#include <sge/opengl/optional_enum.hpp>
#include <sge/opengl/context/base.hpp>
#include <sge/opengl/context/id.hpp>
#include <sge/opengl/info/context_fwd.hpp>
#include <fcppt/nonmovable.hpp>


namespace sge::opengl
{

class multi_sample_context
:
	public sge::opengl::context::base
{
	FCPPT_NONMOVABLE(
		multi_sample_context
	);
public:
	using
	parameter
	=
	sge::opengl::info::context const &;

	explicit
	multi_sample_context(
		sge::opengl::info::context const &
	);

	~multi_sample_context()
	override;

	[[nodiscard]]
	sge::opengl::optional_enum
	flag() const;

	static sge::opengl::context::id const static_id;
private:
	sge::opengl::optional_enum const flag_;
};

}

#endif
