//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_MEDIA_IMPL_RAW_STREAMBUF_HPP_INCLUDED
#define SGE_MEDIA_IMPL_RAW_STREAMBUF_HPP_INCLUDED

#include <sge/core/detail/class_symbol.hpp>
#include <sge/media/const_raw_range.hpp>
#include <sge/media/detail/symbol.hpp>
#include <fcppt/nonmovable.hpp>
#include <fcppt/config/external_begin.hpp>
#include <streambuf>
#include <fcppt/config/external_end.hpp>


namespace sge::media::impl
{

class SGE_CORE_DETAIL_CLASS_SYMBOL raw_streambuf
:
	public
		std::streambuf
{
	FCPPT_NONMOVABLE(
		raw_streambuf
	);
public:
	SGE_MEDIA_DETAIL_SYMBOL
	explicit
	raw_streambuf(
		sge::media::const_raw_range const &
	);

	SGE_MEDIA_DETAIL_SYMBOL
	~raw_streambuf()
	override;
};

}

#endif
