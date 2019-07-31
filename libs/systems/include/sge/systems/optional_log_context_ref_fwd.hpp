//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_SYSTEMS_OPTIONAL_LOG_CONTEXT_REF_FWD_HPP_INCLUDED
#define SGE_SYSTEMS_OPTIONAL_LOG_CONTEXT_REF_FWD_HPP_INCLUDED

#include <fcppt/log/context_fwd.hpp>
#include <fcppt/optional/reference_fwd.hpp>


namespace sge
{
namespace systems
{

typedef
fcppt::optional::reference<
	fcppt::log::context
>
optional_log_context_ref;

}
}

#endif
