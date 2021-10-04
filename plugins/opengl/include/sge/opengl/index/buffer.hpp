//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_OPENGL_INDEX_BUFFER_HPP_INCLUDED
#define SGE_OPENGL_INDEX_BUFFER_HPP_INCLUDED

#include <sge/opengl/common.hpp>
#include <sge/opengl/buffer/object.hpp>
#include <sge/opengl/buffer/wrapper.hpp>
#include <sge/opengl/context/object_ref.hpp>
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
#include <fcppt/nonmovable.hpp>


namespace sge::opengl::index
{

// NOLINTNEXTLINE(fuchsia-multiple-inheritance)
class buffer
:
	public sge::renderer::index::buffer,
	public sge::opengl::buffer::wrapper
{
	FCPPT_NONMOVABLE(
		buffer
	);
public:
	buffer(
		sge::opengl::context::object_ref,
		sge::renderer::index::buffer_parameters const &
	);

	~buffer()
	override;

	[[nodiscard]]
	GLenum
	gl_format() const;

	[[nodiscard]]
	GLvoid *
	buffer_offset(
		sge::renderer::index::first
	) const;

	void
	bind() const;
private:
	[[nodiscard]]
	sge::renderer::index::dynamic::view
	lock(
		sge::renderer::lock_segment const &,
		sge::renderer::lock_mode
	)
	override;

	[[nodiscard]]
	sge::renderer::index::dynamic::const_view
	lock_c(
		sge::renderer::lock_segment const &
	) const
	override;

	template<
		typename View
	>
	[[nodiscard]]
	View
	do_lock(
		sge::renderer::lock_flags::method,
		sge::renderer::lock_segment const &
	) const;

	void
	unlock() const
	override;

	[[nodiscard]]
	sge::renderer::dim1
	size() const
	override;

	[[nodiscard]]
	sge::renderer::resource_flags_field
	resource_flags() const
	override;

	[[nodiscard]]
	sge::renderer::index::dynamic::format
	format() const
	override;

	[[nodiscard]]
	sge::opengl::buffer::object const &
	get() const
	override;

	sge::renderer::index::dynamic::format const format_;

	GLenum const gl_format_;

	mutable sge::opengl::buffer::object buffer_;
};

}

#endif

