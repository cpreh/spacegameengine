//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_OPENAL_CURRENT_CONTEXT_HPP_INCLUDED
#define SGE_OPENAL_CURRENT_CONTEXT_HPP_INCLUDED

#include <sge/openal/context_fwd.hpp>
#include <fcppt/nonmovable.hpp>
#include <fcppt/reference_impl.hpp>
#include <fcppt/log/object_reference.hpp>


namespace sge::openal
{

class current_context
{
	FCPPT_NONMOVABLE(
		current_context
	);
public:
	current_context(
		fcppt::log::object_reference,
		fcppt::reference<
			sge::openal::context
		>
	);

	~current_context();
private:
	fcppt::log::object_reference const log_;

	fcppt::reference<
		sge::openal::context
	> const context_;
};

}

#endif
