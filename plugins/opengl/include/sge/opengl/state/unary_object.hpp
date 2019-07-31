//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_OPENGL_STATE_UNARY_OBJECT_HPP_INCLUDED
#define SGE_OPENGL_STATE_UNARY_OBJECT_HPP_INCLUDED

#include <sge/opengl/state/unary_object_fwd.hpp>
#include <fcppt/function_impl.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/config/external_begin.hpp>
#include <vector>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace opengl
{
namespace state
{

template<
	typename Base,
	typename Parameter
>
class unary_object
:
	public Base
{
	FCPPT_NONCOPYABLE(
		unary_object
	);
public:
	typedef
	fcppt::function<
		void (
			Parameter const &
		)
	>
	actor_type;

	typedef
	std::vector<
		actor_type
	>
	actor_vector;

	explicit
	unary_object(
		actor_vector &&
	);

	~unary_object()
	override;

	void
	set(
		Parameter const &
	) const;
private:
	actor_vector const actors_;
};

}
}
}

#endif
