//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_OPENGL_BACKEND_SCOPED_CURRENT_HPP_INCLUDED
#define SGE_OPENGL_BACKEND_SCOPED_CURRENT_HPP_INCLUDED

#include <sge/opengl/backend/context_fwd.hpp>
#include <sge/opengl/backend/current_fwd.hpp>
#include <sge/opengl/backend/current_unique_ptr.hpp>
#include <sge/opengl/backend/scoped_current_fwd.hpp>
#include <fcppt/noncopyable.hpp>


namespace sge
{
namespace opengl
{
namespace backend
{

class scoped_current
{
	FCPPT_NONCOPYABLE(
		scoped_current
	);
public:
	explicit
	scoped_current(
		sge::opengl::backend::context &
	);

	~scoped_current();

	sge::opengl::backend::current &
	get() const;
private:
	sge::opengl::backend::context &context_;

	sge::opengl::backend::current_unique_ptr current_;
};

}
}
}

#endif
