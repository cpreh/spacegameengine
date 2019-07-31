//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_OPENGL_INDEX_BUFFER_HPP_INCLUDED
#define SGE_OPENGL_INDEX_BUFFER_HPP_INCLUDED

#include <sge/opengl/common.hpp>
#include <sge/opengl/buffer/object.hpp>
#include <sge/opengl/buffer/wrapper.hpp>
#include <sge/opengl/context/object_fwd.hpp>
#include <sge/renderer/dim1_fwd.hpp>
#include <sge/renderer/lock_mode_fwd.hpp>
#include <sge/renderer/lock_segment_fwd.hpp>
#include <sge/renderer/resource_flags_field_fwd.hpp>
#include <sge/renderer/index/buffer.hpp>
#include <sge/renderer/index/buffer_parameters_fwd.hpp>
#include <sge/renderer/index/first.hpp>
#include <sge/renderer/index/dynamic/const_view_fwd.hpp>
#include <sge/renderer/index/dynamic/format.hpp>
#include <sge/renderer/index/dynamic/view_fwd.hpp>
#include <sge/renderer/lock_flags/method_fwd.hpp>
#include <fcppt/noncopyable.hpp>


namespace sge
{
namespace opengl
{
namespace index
{

class buffer
:
	public sge::renderer::index::buffer,
	public sge::opengl::buffer::wrapper
{
	FCPPT_NONCOPYABLE(
		buffer
	);
public:
	buffer(
		sge::opengl::context::object &,
		sge::renderer::index::buffer_parameters const &
	);

	~buffer()
	override;

	GLenum
	gl_format() const;

	GLvoid *
	buffer_offset(
		sge::renderer::index::first
	) const;

	void
	bind() const;
private:
	sge::renderer::index::dynamic::view
	lock(
		sge::renderer::lock_segment const &,
		sge::renderer::lock_mode
	)
	override;

	sge::renderer::index::dynamic::const_view
	lock_c(
		sge::renderer::lock_segment const &
	) const
	override;

	template<
		typename View
	>
	View
	do_lock(
		sge::renderer::lock_flags::method,
		sge::renderer::lock_segment const &
	) const;

	void
	unlock() const
	override;

	sge::renderer::dim1
	size() const
	override;

	sge::renderer::resource_flags_field
	resource_flags() const
	override;

	sge::renderer::index::dynamic::format
	format() const
	override;

	sge::opengl::buffer::object const &
	get() const
	override;

	sge::renderer::index::dynamic::format const format_;

	GLenum const gl_format_;

	mutable sge::opengl::buffer::object buffer_;
};

}
}
}

#endif

