//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/libpng/header_bytes.hpp>
#include <sge/libpng/is_png.hpp>
#include <sge/libpng/png.hpp>
#include <fcppt/literal.hpp>
#include <fcppt/no_init.hpp>
#include <fcppt/array/object_impl.hpp>
#include <fcppt/cast/size.hpp>
#include <fcppt/cast/to_char_ptr.hpp>
#include <fcppt/cast/to_signed.hpp>
#include <fcppt/config/external_begin.hpp>
#include <ios>
#include <istream>
#include <fcppt/config/external_end.hpp>

bool sge::libpng::is_png(std::istream &_stream)
{
  fcppt::array::object<char, sge::libpng::header_bytes::value> buf{fcppt::no_init{}};

  std::streamsize const signed_size(fcppt::cast::to_signed(buf.size()));

  _stream.read(buf.data(), signed_size);

  return _stream.gcount() >= signed_size && ::png_sig_cmp(
                                                fcppt::cast::to_char_ptr<png_byte *>(buf.data()),
                                                fcppt::literal<png_size_t>(0),
                                                fcppt::cast::size<png_size_t>(buf.size())) == 0;
}
