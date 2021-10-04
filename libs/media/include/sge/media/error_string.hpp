//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_MEDIA_ERROR_STRING_HPP_INCLUDED
#define SGE_MEDIA_ERROR_STRING_HPP_INCLUDED

#include <sge/media/optional_name_fwd.hpp>
#include <sge/media/detail/symbol.hpp>
#include <fcppt/string.hpp>


namespace sge::media
{

SGE_MEDIA_DETAIL_SYMBOL
fcppt::string
error_string(
	sge::media::optional_name const &,
	fcppt::string const &
);

}

#endif
