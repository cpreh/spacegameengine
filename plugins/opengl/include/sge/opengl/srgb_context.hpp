//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_OPENGL_SRGB_CONTEXT_HPP_INCLUDED
#define SGE_OPENGL_SRGB_CONTEXT_HPP_INCLUDED

#include <sge/opengl/optional_enum.hpp>
#include <sge/opengl/srgb_context_fwd.hpp>
#include <sge/opengl/context/base.hpp>
#include <sge/opengl/context/id.hpp>
#include <sge/opengl/info/context_fwd.hpp>
#include <fcppt/nonmovable.hpp>


namespace sge::opengl
{

class srgb_context
:
	public sge::opengl::context::base
{
	FCPPT_NONMOVABLE(
		srgb_context
	);
public:
	using
	parameter
	=
	sge::opengl::info::context const &;

	explicit
	srgb_context(
		sge::opengl::info::context const &
	);

	~srgb_context()
	override;

	[[nodiscard]]
	sge::opengl::optional_enum
	flag() const;

	static
	sge::opengl::context::id const
	static_id;
private:
	sge::opengl::optional_enum const flag_;
};

}

#endif
