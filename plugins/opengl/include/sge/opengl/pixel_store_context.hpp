//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_OPENGL_PIXEL_STORE_CONTEXT_HPP_INCLUDED
#define SGE_OPENGL_PIXEL_STORE_CONTEXT_HPP_INCLUDED

#include <sge/opengl/pixel_store_context_fwd.hpp>
#include <sge/opengl/unpack_alignment.hpp>
#include <sge/opengl/context/base.hpp>
#include <sge/opengl/context/id.hpp>
#include <fcppt/nonmovable.hpp>


namespace sge::opengl
{

class pixel_store_context
:
	public sge::opengl::context::base
{
	FCPPT_NONMOVABLE(
		pixel_store_context
	);
public:
	pixel_store_context();

	~pixel_store_context()
	override;

	void
	unpack_alignment(
		sge::opengl::unpack_alignment
	);

	[[nodiscard]]
	sge::opengl::unpack_alignment
	unpack_alignment() const;

	using
	parameter
	=
	void;

	static sge::opengl::context::id const static_id;
private:
	sge::opengl::unpack_alignment unpack_alignment_;
};

}

#endif
