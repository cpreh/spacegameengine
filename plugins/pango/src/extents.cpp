//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/pango/extents.hpp>
#include <sge/pango/ink_rect.hpp>
#include <sge/pango/logical_rect.hpp>
#include <fcppt/config/external_begin.hpp>
#include <utility>
#include <fcppt/config/external_end.hpp>


sge::pango::extents::extents(
	sge::pango::ink_rect _ink_rect,
	sge::pango::logical_rect _logical_rect
)
:
	ink_rect_{
		std::move(
			_ink_rect
		)
	},
	logical_rect_{
		std::move(
			_logical_rect
		)
	}
{
}

sge::pango::ink_rect
sge::pango::extents::ink_rect() const
{
	return
		ink_rect_;
}

sge::pango::logical_rect
sge::pango::extents::logical_rect() const
{
	return
		logical_rect_;
}
