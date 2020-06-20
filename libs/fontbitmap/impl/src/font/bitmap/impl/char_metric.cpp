//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/font/unit.hpp>
#include <sge/font/vector.hpp>
#include <sge/font/bitmap/impl/char_metric.hpp>
#include <sge/font/bitmap/impl/const_view.hpp>
#include <fcppt/config/external_begin.hpp>
#include <utility>
#include <fcppt/config/external_end.hpp>


sge::font::bitmap::impl::char_metric::char_metric(
	sge::font::bitmap::impl::const_view _view,
	sge::font::vector _offset,
	sge::font::unit const _x_advance
)
:
	view_(
		std::move(
			_view
		)
	),
	offset_(
		std::move(
			_offset
		)
	),
	x_advance_(
		_x_advance
	)
{
}

sge::font::bitmap::impl::const_view
sge::font::bitmap::impl::char_metric::view() const
{
	return
		view_;
}

sge::font::vector
sge::font::bitmap::impl::char_metric::offset() const
{
	return
		offset_;
}

sge::font::unit
sge::font::bitmap::impl::char_metric::x_advance() const
{
	return
		x_advance_;
}
