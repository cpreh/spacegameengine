//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/font/unit.hpp>
#include <sge/font/bitmap/impl/char_metric_ref_vector.hpp>
#include <sge/font/bitmap/impl/line.hpp>


sge::font::bitmap::impl::line::line(
	sge::font::bitmap::impl::char_metric_ref_vector const &_char_metrics,
	sge::font::unit const _width
)
:
	char_metrics_(
		_char_metrics
	),
	width_(
		_width
	)
{
}

sge::font::bitmap::impl::line::line(
	line &&
) = default;

sge::font::bitmap::impl::line &
sge::font::bitmap::impl::line::operator=(
	line &&
) = default;

sge::font::bitmap::impl::line::~line()
{
}

sge::font::bitmap::impl::char_metric_ref_vector const &
sge::font::bitmap::impl::line::char_metrics() const
{
	return
		char_metrics_;
}

sge::font::unit
sge::font::bitmap::impl::line::width() const
{
	return
		width_;
}
