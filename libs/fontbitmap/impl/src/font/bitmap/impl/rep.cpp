//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/font/rect.hpp>
#include <sge/font/bitmap/impl/line_vector.hpp>
#include <sge/font/bitmap/impl/rep.hpp>
#include <fcppt/config/external_begin.hpp>
#include <utility>
#include <fcppt/config/external_end.hpp>


sge::font::bitmap::impl::rep::rep(
	sge::font::bitmap::impl::line_vector &&_lines,
	sge::font::rect _rect
)
:
	lines_(
		std::move(
			_lines
		)
	),
	rect_(
		std::move(
			_rect
		)
	)
{
}

sge::font::bitmap::impl::line_vector const &
sge::font::bitmap::impl::rep::lines() const
{
	return
		lines_;
}

sge::font::rect
sge::font::bitmap::impl::rep::rect() const
{
	return
		rect_;
}
