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
#include <fcppt/nonmovable.hpp>


namespace sge
{
namespace opengl
{
namespace texture
{

class lock_base
{
	FCPPT_NONMOVABLE(
		lock_base
	);
protected:
	lock_base();
public:
	using
	size_type
	=
	sge::renderer::size_type;

	using
	value_type
	=
	sge::renderer::raw_value;

	using
	pointer
	=
	value_type *;

	using
	const_pointer
	=
	value_type const *;

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

	[[nodiscard]]
	virtual
	pointer
	read_pointer() = 0;

	[[nodiscard]]
	virtual
	pointer
	write_pointer() = 0;

	[[nodiscard]]
	virtual
	pointer
	read_view_pointer() = 0;

	[[nodiscard]]
	virtual
	pointer
	write_view_pointer() = 0;

	[[nodiscard]]
	virtual
	sge::renderer::lock_flags::method
	method() const = 0;
};

}
}
}

#endif
