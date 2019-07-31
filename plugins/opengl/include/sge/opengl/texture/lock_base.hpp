//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_OPENGL_TEXTURE_LOCK_BASE_HPP_INCLUDED
#define SGE_OPENGL_TEXTURE_LOCK_BASE_HPP_INCLUDED

#include <sge/opengl/texture/lock_base_fwd.hpp>
#include <sge/renderer/raw_value.hpp>
#include <sge/renderer/size_type.hpp>
#include <sge/renderer/lock_flags/method_fwd.hpp>
#include <fcppt/noncopyable.hpp>


namespace sge
{
namespace opengl
{
namespace texture
{

class lock_base
{
	FCPPT_NONCOPYABLE(
		lock_base
	);
protected:
	lock_base();
public:
	typedef sge::renderer::size_type size_type;

	typedef sge::renderer::raw_value value_type;

	typedef value_type *pointer;

	typedef value_type const *const_pointer;

	virtual
	~lock_base();

	virtual
	void
	lock() = 0;

	virtual
	void
	unlock() = 0;

	virtual
	void
	pre_unlock() = 0;

	virtual
	void
	post_copy() = 0;

	virtual
	pointer
	read_pointer() = 0;

	virtual
	pointer
	write_pointer() = 0;

	virtual
	pointer
	read_view_pointer() = 0;

	virtual
	pointer
	write_view_pointer() = 0;

	virtual
	sge::renderer::lock_flags::method
	method() const = 0;
};

}
}
}

#endif
