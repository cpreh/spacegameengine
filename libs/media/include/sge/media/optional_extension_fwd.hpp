//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_MEDIA_OPTIONAL_EXTENSION_FWD_HPP_INCLUDED
#define SGE_MEDIA_OPTIONAL_EXTENSION_FWD_HPP_INCLUDED

#include <sge/media/extension_fwd.hpp>
#include <fcppt/optional/object_fwd.hpp>


namespace sge
{
namespace media
{

typedef
fcppt::optional::object<
	sge::media::extension
>
optional_extension;

}
}

#endif
