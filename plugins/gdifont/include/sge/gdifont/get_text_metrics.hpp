//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_GDIFONT_GET_TEXT_METRICS_HPP_INCLUDED
#define SGE_GDIFONT_GET_TEXT_METRICS_HPP_INCLUDED

#include <sge/gdifont/device_context_fwd.hpp>
#include <sge/gdifont/include_windows.hpp>


namespace sge
{
namespace gdifont
{

TEXTMETRIC const
get_text_metrics(
	sge::gdifont::device_context const &
);

}
}

#endif
