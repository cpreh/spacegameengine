//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/image/size_type.hpp>
#include <sge/opengl/stride_to_unpack_alignment.hpp>
#include <sge/opengl/unpack_alignment.hpp>
#include <sge/renderer/opengl/glinclude.hpp>
#include <fcppt/cast/size.hpp>
#include <fcppt/cast/to_signed.hpp>

sge::opengl::unpack_alignment
sge::opengl::stride_to_unpack_alignment(sge::image::size_type const _stride)
{
  for (GLint divisor(8 // NOLINT(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
       );
       divisor != 1;
       divisor /= 2)
  {
    if ((fcppt::cast::size<GLint>(fcppt::cast::to_signed(_stride)) % divisor) == 0)
    {
      return sge::opengl::unpack_alignment(divisor);
    }
  }

  return sge::opengl::unpack_alignment(1);
}
