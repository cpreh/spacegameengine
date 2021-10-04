//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_OPENGL_STATE_FFP_MISC_DEFAULT_CONTEXT_HPP_INCLUDED
#define SGE_OPENGL_STATE_FFP_MISC_DEFAULT_CONTEXT_HPP_INCLUDED

#include <sge/opengl/context/base.hpp>
#include <sge/opengl/context/id.hpp>
#include <sge/opengl/state/ffp/misc/default_context_parameters_fwd.hpp>
#include <sge/opengl/state/ffp/misc/object_fwd.hpp>
#include <fcppt/nonmovable.hpp>
#include <fcppt/unique_ptr_impl.hpp>


namespace sge::opengl::state::ffp::misc
{

class default_context
:
	public sge::opengl::context::base
{
	FCPPT_NONMOVABLE(
		default_context
	);
public:
	using
	parameter
	=
	sge::opengl::state::ffp::misc::default_context_parameters;

	explicit
	default_context(
		parameter
	);

	~default_context()
	override;

	[[nodiscard]]
	sge::opengl::state::ffp::misc::object const &
	default_state() const;

	static
	sge::opengl::context::id const
	static_id;
private:
	using
	object_unique_ptr
	=
	fcppt::unique_ptr<
		sge::opengl::state::ffp::misc::object
	>;

	object_unique_ptr const default_state_;
};

}

#endif
