//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_OPENGL_BUFFER_HOLDER_HPP_INCLUDED
#define SGE_OPENGL_BUFFER_HOLDER_HPP_INCLUDED

#include <sge/opengl/buffer/base_fwd.hpp>
#include <sge/opengl/buffer/id.hpp>
#include <fcppt/noncopyable.hpp>

namespace sge
{
namespace opengl
{
namespace buffer
{

class holder
{
	FCPPT_NONCOPYABLE(
		holder
	);
public:
	explicit
	holder(
		sge::opengl::buffer::base &
	);

	~holder();

	sge::opengl::buffer::id
	id() const;
private:
	sge::opengl::buffer::base &base_;

	sge::opengl::buffer::id const id_;
};

}
}
}

#endif
