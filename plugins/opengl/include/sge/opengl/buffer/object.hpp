//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_OPENGL_BUFFER_OBJECT_HPP_INCLUDED
#define SGE_OPENGL_BUFFER_OBJECT_HPP_INCLUDED

#include <sge/opengl/buffer/base_fwd.hpp>
#include <sge/opengl/buffer/holder.hpp>
#include <sge/opengl/buffer/id.hpp>
#include <sge/opengl/buffer/object_fwd.hpp>
#include <sge/opengl/buffer/optional_id_fwd.hpp>
#include <sge/renderer/raw_value.hpp>
#include <sge/renderer/resource_flags_field.hpp>
#include <sge/renderer/size_type.hpp>
#include <sge/renderer/lock_flags/method_fwd.hpp>
#include <fcppt/noncopyable.hpp>


namespace sge
{
namespace opengl
{
namespace buffer
{

class object
{
	FCPPT_NONCOPYABLE(
		object
	);
public:
	typedef sge::renderer::size_type size_type;

	typedef sge::renderer::raw_value value_type;

	typedef value_type *pointer;

	typedef value_type const *const_pointer;

	typedef sge::renderer::lock_flags::method lock_flag_type;

	object(
		sge::opengl::buffer::base &,
		size_type size,
		size_type stride,
		sge::renderer::resource_flags_field const &,
		const_pointer src
	);

	~object();

	static size_type const npos = static_cast<size_type>(-1);

	void
	lock(
		lock_flag_type const &,
		size_type first = 0,
		size_type count = npos
	);

	void
	unlock();

	void
	sub_data(
		const_pointer data,
		size_type first,
		size_type count
	);

	size_type
	size() const;

	size_type
	stride() const;

	sge::renderer::resource_flags_field const &
	flags() const;

	pointer
	data();

	const_pointer
	data() const;

	size_type
	lock_size() const;

	void
	unbind();

	void
	bind() const;

	pointer
	buffer_offset(
		size_type offset
	) const;

	pointer
	raw_buffer() const;

	sge::opengl::buffer::id
	id() const;

	bool
	native() const;
private:
	void
	bind_id(
		sge::opengl::buffer::optional_id const &
	) const;

	sge::opengl::buffer::base &base_;

	size_type const
		size_,
		stride_;

	sge::renderer::resource_flags_field const flags_;

	pointer dest_;

	sge::opengl::buffer::holder const holder_;

	size_type
		lock_offset_,
		lock_size_;
};

}
}
}

#endif
