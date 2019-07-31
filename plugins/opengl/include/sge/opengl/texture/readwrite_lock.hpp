//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_OPENGL_TEXTURE_READWRITE_LOCK_HPP_INCLUDED
#define SGE_OPENGL_TEXTURE_READWRITE_LOCK_HPP_INCLUDED

#include <sge/opengl/context/object_fwd.hpp>
#include <sge/opengl/texture/lock_base.hpp>
#include <sge/opengl/texture/readonly_lock.hpp>
#include <sge/opengl/texture/writeonly_lock.hpp>
#include <sge/renderer/resource_flags_field_fwd.hpp>
#include <sge/renderer/lock_flags/method_fwd.hpp>
#include <fcppt/noncopyable.hpp>


namespace sge
{
namespace opengl
{
namespace texture
{

class readwrite_lock
:
	public sge::opengl::texture::lock_base
{
	FCPPT_NONCOPYABLE(
		readwrite_lock
	);
public:
	readwrite_lock(
		sge::opengl::context::object &,
		size_type read_size,
		size_type write_size,
		size_type stride,
		sge::renderer::resource_flags_field const &
	);

	~readwrite_lock()
	override;
private:
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

	sge::renderer::lock_flags::method
	method() const
	override;

	sge::opengl::texture::readonly_lock read_lock_;

	sge::opengl::texture::writeonly_lock write_lock_;
};

}
}
}

#endif
