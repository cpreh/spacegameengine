//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_FONT_ALIGN_H_LEFT_HPP_INCLUDED
#define SGE_FONT_ALIGN_H_LEFT_HPP_INCLUDED

#include <sge/font/align_h/left_fwd.hpp>
#include <sge/font/align_h/max_width.hpp>
#include <sge/font/align_h/optional_max_width.hpp>
#include <sge/font/detail/symbol.hpp>


namespace sge::font::align_h
{

class left
{
public:
	SGE_FONT_DETAIL_SYMBOL
	left();

	SGE_FONT_DETAIL_SYMBOL
	explicit
	left(
		sge::font::align_h::max_width
	);

	[[nodiscard]]
	SGE_FONT_DETAIL_SYMBOL
	sge::font::align_h::optional_max_width
	max_width() const;
private:
	sge::font::align_h::optional_max_width max_width_;
};

}

#endif
