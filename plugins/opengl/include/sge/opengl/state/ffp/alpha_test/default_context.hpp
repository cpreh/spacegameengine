//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_OPENGL_STATE_FFP_ALPHA_TEST_DEFAULT_CONTEXT_HPP_INCLUDED
#define SGE_OPENGL_STATE_FFP_ALPHA_TEST_DEFAULT_CONTEXT_HPP_INCLUDED

#include <sge/opengl/context/base.hpp>
#include <sge/opengl/context/id.hpp>
#include <sge/opengl/state/ffp/alpha_test/object_fwd.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/unique_ptr_impl.hpp>


namespace sge
{
namespace opengl
{
namespace state
{
namespace ffp
{
namespace alpha_test
{

class default_context
:
	public sge::opengl::context::base
{
	FCPPT_NONCOPYABLE(
		default_context
	);
public:
	typedef void parameter;

	default_context();

	~default_context()
	override;

	sge::opengl::state::ffp::alpha_test::object const &
	default_state() const;

	static
	sge::opengl::context::id const
	static_id;
private:
	typedef
	fcppt::unique_ptr<
		sge::opengl::state::ffp::alpha_test::object
	>
	object_unique_ptr;

	object_unique_ptr const default_state_;
};

}
}
}
}
}

#endif
