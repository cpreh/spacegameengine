//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_PANGO_GLIB_DELETER_HPP_INCLUDED
#define SGE_PANGO_GLIB_DELETER_HPP_INCLUDED

#include <sge/pango/glib_deleter_fwd.hpp>
#include <fcppt/config/external_begin.hpp>
#include <glib.h>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace pango
{

struct glib_deleter
{
	void
	operator()(
		gpointer
	);
};

}
}

#endif
