//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_OPENGL_BUFFER_SOFTWARE_HPP_INCLUDED
#define SGE_OPENGL_BUFFER_SOFTWARE_HPP_INCLUDED

#include <sge/opengl/common.hpp>
#include <sge/opengl/buffer/base.hpp>
#include <sge/opengl/buffer/id.hpp>
#include <sge/opengl/buffer/optional_id.hpp>
#include <sge/renderer/const_raw_pointer.hpp>
#include <sge/renderer/raw_pointer.hpp>
#include <fcppt/nonmovable.hpp>
#include <fcppt/config/external_begin.hpp>
#include <unordered_map>
#include <fcppt/config/external_end.hpp>


namespace sge::opengl::buffer
{

class software
:
	public sge::opengl::buffer::base
{
	FCPPT_NONMOVABLE(
		software
	);
public:
	software();

	~software()
	override;
private:
	[[nodiscard]]
	sge::opengl::buffer::id
	gen_buffer()
	override;

	void
	delete_buffer(
		sge::opengl::buffer::id
	)
	override;

	void
	bind_buffer(
		sge::opengl::buffer::optional_id const &
	)
	override;

	[[nodiscard]]
	GLvoid *
	map_buffer(
		GLenum flags
	)
	override;

	[[nodiscard]]
	GLvoid *
	map_buffer_range(
		GLbitfield flags,
		GLintptr first,
		GLsizeiptr size
	)
	override;

	[[nodiscard]]
	bool
	map_buffer_range_supported() const
	override;

	void
	unmap_buffer()
	override;

	void
	buffer_data(
		GLsizeiptr size,
		GLvoid const *data,
		GLenum flags
	)
	override;

	void
	buffer_sub_data(
		GLintptr first,
		GLsizeiptr size,
		GLvoid const *data
	)
	override;

	[[nodiscard]]
	void *
	buffer_offset(
		GLintptr offset
	) const
	override;

	[[nodiscard]]
	bool
	native() const
	override;

	[[nodiscard]]
	sge::opengl::buffer::id
	bound_buffer() const;

	using
	buffer_map
	=
	std::unordered_map<
		sge::opengl::buffer::id,
		sge::renderer::raw_pointer
	>;

	[[nodiscard]]
	sge::renderer::raw_pointer &
	buffer_object(
		sge::opengl::buffer::id
	);

	[[nodiscard]]
	sge::renderer::const_raw_pointer
	buffer_object(
		sge::opengl::buffer::id
	) const;

	sge::opengl::buffer::optional_id bound_buffer_;

	sge::opengl::buffer::id nextid_;

	buffer_map buffers_;
};

}

#endif
