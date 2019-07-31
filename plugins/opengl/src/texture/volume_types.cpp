//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/opengl/texture/volume_types.hpp>
#include <fcppt/string.hpp>
#include <fcppt/text.hpp>


fcppt::string
sge::opengl::texture::volume_types::name()
{
	return
		FCPPT_TEXT("volume texture");
}
