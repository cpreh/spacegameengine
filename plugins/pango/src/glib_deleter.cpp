//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/pango/glib_deleter.hpp>
#include <fcppt/config/external_begin.hpp>
#include <glib-object.h>
#include <glib.h>
#include <fcppt/config/external_end.hpp>


void
sge::pango::glib_deleter::operator()(
	gpointer const _ptr
)
{
	if(
		_ptr != nullptr
	)
		::g_object_unref(
			_ptr
		);
}
