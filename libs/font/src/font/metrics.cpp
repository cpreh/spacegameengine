//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/font/height.hpp>
#include <sge/font/metrics.hpp>


sge::font::metrics::metrics(
	sge::font::height const _height
)
:
	height_{
		_height
	}
{
}

sge::font::height
sge::font::metrics::height() const
{
	return
		height_;
}
