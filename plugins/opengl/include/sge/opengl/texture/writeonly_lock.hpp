//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_OPENGL_TEXTURE_WRITEONLY_LOCK_HPP_INCLUDED
#define SGE_OPENGL_TEXTURE_WRITEONLY_LOCK_HPP_INCLUDED

#include <sge/opengl/buffer/object.hpp>
#include <sge/opengl/context/object_fwd.hpp>
#include <sge/opengl/texture/lock_base.hpp>
#include <sge/renderer/resource_flags_field_fwd.hpp>
#include <sge/renderer/lock_flags/method_fwd.hpp>
#include <fcppt/noncopyable.hpp>


namespace sge
{
namespace opengl
{
namespace texture
{

class writeonly_lock
:
	public sge::opengl::texture::lock_base
{
	FCPPT_NONCOPYABLE(
		writeonly_lock
	);
public:
	writeonly_lock(
		sge::opengl::context::object &,
		size_type lock_size,
		size_type stride,
		sge::renderer::resource_flags_field const &
	);

	~writeonly_lock()
	override;

	void
	lock()
	override;

	void
	unlock()
	override;

	void
	pre_unlock()
	override;

	void
	post_copy()
	override;

	pointer
	read_pointer()
	override;

	pointer
	write_pointer()
	override;

	pointer
	read_view_pointer()
	override;

	pointer
	write_view_pointer()
	override;
private:
	sge::renderer::lock_flags::method
	method() const
	override;

	sge::opengl::buffer::object buffer_;
};

}
}
}

#endif
