//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_OPENGL_BUFFER_PBO_CONTEXT_HPP_INCLUDED
#define SGE_OPENGL_BUFFER_PBO_CONTEXT_HPP_INCLUDED

#include <sge/opengl/buffer/base_fwd.hpp>
#include <sge/opengl/buffer/base_unique_ptr.hpp>
#include <sge/opengl/context/base.hpp>
#include <sge/opengl/context/id.hpp>
#include <sge/opengl/context/object_ref.hpp>
#include <fcppt/nonmovable.hpp>
#include <fcppt/config/external_begin.hpp>
#include <array>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace opengl
{
namespace buffer
{

class pbo_context
:
	public sge::opengl::context::base
{
	FCPPT_NONMOVABLE(
		pbo_context
	);
public:
	using
	parameter
	=
	sge::opengl::context::object_ref;

	explicit
	pbo_context(
		parameter
	);

	~pbo_context()
	override;

	[[nodiscard]]
	sge::opengl::buffer::base &
	pack_buffer() const;

	[[nodiscard]]
	sge::opengl::buffer::base &
	unpack_buffer() const;

	static sge::opengl::context::id const static_id;
private:
	using
	buffer_array
	=
	std::array<
		sge::opengl::buffer::base_unique_ptr,
		2U
	>;

	buffer_array const buffers_;
};

}
}
}

#endif
