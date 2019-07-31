//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_OPENGL_STATE_OBJECT_HPP_INCLUDED
#define SGE_OPENGL_STATE_OBJECT_HPP_INCLUDED

#include <sge/opengl/state/actor_vector.hpp>
#include <sge/opengl/state/object_fwd.hpp>
#include <fcppt/noncopyable.hpp>


namespace sge
{
namespace opengl
{
namespace state
{

template<
	typename Base
>
class object
:
	public Base
{
	FCPPT_NONCOPYABLE(
		object
	);
public:
	explicit
	object(
		sge::opengl::state::actor_vector const &
	);

	~object()
	override;

	void
	set() const;
private:
	sge::opengl::state::actor_vector const actors_;
};

}
}
}

#endif
