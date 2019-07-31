//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_IMAGE_DS_FORMAT_HPP_INCLUDED
#define SGE_IMAGE_DS_FORMAT_HPP_INCLUDED

#include <sge/image/ds/format_fwd.hpp>


namespace sge
{
namespace image
{
namespace ds
{

enum class format
{
	d16,
	d32,
	d24s8,
	fcppt_maximum = d24s8
};

}
}
}

#endif
