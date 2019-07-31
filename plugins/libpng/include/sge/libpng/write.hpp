//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_LIBPNG_WRITE_HPP_INCLUDED
#define SGE_LIBPNG_WRITE_HPP_INCLUDED

#include <sge/libpng/file_rep_fwd.hpp>
#include <sge/media/optional_name_fwd.hpp>
#include <fcppt/log/object_fwd.hpp>
#include <fcppt/config/external_begin.hpp>
#include <iosfwd>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace libpng
{

void
write(
	fcppt::log::object &,
	std::ostream &,
	sge::media::optional_name const &,
	sge::libpng::file_rep const &
);

}
}

#endif
