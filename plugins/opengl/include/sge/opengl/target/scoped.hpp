//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_OPENGL_TARGET_SCOPED_HPP_INCLUDED
#define SGE_OPENGL_TARGET_SCOPED_HPP_INCLUDED

#include <sge/opengl/target/base_fwd.hpp>
#include <sge/opengl/target/scoped_fwd.hpp>
#include <fcppt/noncopyable.hpp>


namespace sge
{
namespace opengl
{
namespace target
{

class scoped
{
	FCPPT_NONCOPYABLE(
		scoped
	);
public:
	explicit
	scoped(
		sge::opengl::target::base &
	);

	~scoped();

	sge::opengl::target::base &
	get() const;
private:
	sge::opengl::target::base &target_;
};

}
}
}

#endif
