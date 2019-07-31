//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_MEDIA_CHECK_EXTENSION_HPP_INCLUDED
#define SGE_MEDIA_CHECK_EXTENSION_HPP_INCLUDED

#include <sge/media/extension_fwd.hpp>
#include <sge/media/optional_extension_fwd.hpp>
#include <sge/media/detail/symbol.hpp>


namespace sge
{
namespace media
{

SGE_MEDIA_DETAIL_SYMBOL
bool
check_extension(
	sge::media::extension const &,
	sge::media::optional_extension const &
);

}
}

#endif
