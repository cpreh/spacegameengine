//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_IMAGE2D_FILE_EXCEPTION_FWD_HPP_INCLUDED
#define SGE_IMAGE2D_FILE_EXCEPTION_FWD_HPP_INCLUDED

#include <sge/image2d/exception_fwd.hpp>
#include <sge/media/file_exception_fwd.hpp>


namespace sge::image2d
{

using
file_exception
=
sge::media::file_exception<
	sge::image2d::exception
>;

}

#endif
