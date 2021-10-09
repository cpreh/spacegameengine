//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_IMAGE_IMPL_PIXEL_OBJECT_OUTPUT_IMPL_HPP_INCLUDED
#define SGE_IMAGE_IMPL_PIXEL_OBJECT_OUTPUT_IMPL_HPP_INCLUDED

#include <sge/image/pixel/object.hpp>
#include <sge/image/pixel/object_output.hpp>
#include <sge/image/pixel/print.hpp>
#include <fcppt/io/ostream_fwd.hpp>
#include <fcppt/variant/apply.hpp>

template <typename Tag>
fcppt::io::ostream &sge::image::pixel::operator<<(
    fcppt::io::ostream &_stream, sge::image::pixel::object<Tag> const &_object)
{
  return fcppt::variant::apply(
      [&_stream](auto const &_value) -> fcppt::io::ostream & { return _stream << _value; },
      _object.get());
}

#endif
