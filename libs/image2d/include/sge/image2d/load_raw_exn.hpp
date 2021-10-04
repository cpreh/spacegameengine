//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_IMAGE2D_LOAD_RAW_EXN_HPP_INCLUDED
#define SGE_IMAGE2D_LOAD_RAW_EXN_HPP_INCLUDED

#include <sge/image2d/file_unique_ptr.hpp>
#include <sge/image2d/system_ref.hpp>
#include <sge/image2d/detail/symbol.hpp>
#include <sge/media/const_raw_range.hpp>
#include <sge/media/optional_extension_fwd.hpp>


namespace sge::image2d
{

SGE_IMAGE2D_DETAIL_SYMBOL
sge::image2d::file_unique_ptr
load_raw_exn(
	sge::image2d::system_ref,
	sge::media::const_raw_range const &,
	sge::media::optional_extension const &
);

}

#endif
