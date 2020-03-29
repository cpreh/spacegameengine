//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_LOG_APPLY_OPTIONS_HPP_INCLUDED
#define SGE_LOG_APPLY_OPTIONS_HPP_INCLUDED

#include <sge/log/option_container.hpp>
#include <sge/log/detail/symbol.hpp>
#include <fcppt/log/context_reference_fwd.hpp>


namespace sge
{
namespace log
{

SGE_LOG_DETAIL_SYMBOL
void
apply_options(
	fcppt::log::context_reference,
	sge::log::option_container const &
);

}
}

#endif
