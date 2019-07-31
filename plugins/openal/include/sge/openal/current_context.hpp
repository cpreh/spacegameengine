//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_OPENAL_CURRENT_CONTEXT_HPP_INCLUDED
#define SGE_OPENAL_CURRENT_CONTEXT_HPP_INCLUDED

#include <sge/openal/context_fwd.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/log/object_fwd.hpp>


namespace sge
{
namespace openal
{

class current_context
{
	FCPPT_NONCOPYABLE(
		current_context
	);
public:
	current_context(
		fcppt::log::object &,
		sge::openal::context &
	);

	~current_context();
private:
	fcppt::log::object &log_;

	sge::openal::context &context_;
};

}
}

#endif
