//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_LIBPNG_FILE_REP_FROM_VIEW_HPP_INCLUDED
#define SGE_LIBPNG_FILE_REP_FROM_VIEW_HPP_INCLUDED

#include <sge/image2d/view/const_object_fwd.hpp>
#include <sge/libpng/optional_file_rep.hpp>


namespace sge
{
namespace libpng
{

sge::libpng::optional_file_rep
file_rep_from_view(
	sge::image2d::view::const_object const &
);

}
}

#endif
