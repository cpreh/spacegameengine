//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_MEDIA_PATH_TO_EXTENSION_HPP_INCLUDED
#define SGE_MEDIA_PATH_TO_EXTENSION_HPP_INCLUDED

#include <sge/media/optional_extension.hpp>
#include <sge/media/detail/symbol.hpp>
#include <fcppt/config/external_begin.hpp>
#include <filesystem>
#include <fcppt/config/external_end.hpp>


namespace sge::media
{

SGE_MEDIA_DETAIL_SYMBOL
sge::media::optional_extension
path_to_extension(
	std::filesystem::path const &
);

}

#endif
