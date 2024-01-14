//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

// something is broken in png.h :(
#include <fcppt/config/external_begin.hpp>
#include <png.h>
#include <fcppt/config/external_end.hpp>
#include <sge/image2d/dim.hpp>
#include <sge/image2d/file_exception.hpp>
#include <sge/libpng/bit_depth.hpp>
#include <sge/libpng/byte_vector.hpp>
#include <sge/libpng/bytes_per_pixel.hpp>
#include <sge/libpng/color_type.hpp>
#include <sge/libpng/error_context.hpp>
#include <sge/libpng/file_rep.hpp>
#include <sge/libpng/file_rep_from_stream.hpp>
#include <sge/libpng/format.hpp>
#include <sge/libpng/get_gamma.hpp>
#include <sge/libpng/header_bytes.hpp>
#include <sge/libpng/info.hpp>
#include <sge/libpng/load_context.hpp>
#include <sge/libpng/make_format.hpp>
#include <sge/libpng/make_row_vector.hpp>
#include <sge/libpng/optional_file_rep.hpp>
#include <sge/libpng/read_ptr.hpp>
#include <sge/libpng/row_vector.hpp>
#include <sge/media/error_string.hpp>
#include <sge/media/optional_name_fwd.hpp>
#include <fcppt/make_ref.hpp>
#include <fcppt/text.hpp>
#include <fcppt/cast/promote_int.hpp>
#include <fcppt/cast/to_unsigned.hpp>
#include <fcppt/container/buffer/object_impl.hpp>
#include <fcppt/container/buffer/read_from.hpp>
#include <fcppt/container/buffer/to_raw_vector.hpp>
#include <fcppt/log/debug.hpp>
#include <fcppt/log/info.hpp>
#include <fcppt/log/object_fwd.hpp>
#include <fcppt/log/out.hpp>
#include <fcppt/math/dim/contents.hpp>
#include <fcppt/math/dim/output.hpp> // NOLINT(misc-include-cleaner)
#include <fcppt/optional/maybe.hpp>
#include <fcppt/config/external_begin.hpp> // NOLINT(readability-duplicate-include)
#include <png.h> // NOLINT(readability-duplicate-include)
#include <pngconf.h>
#include <climits>
#include <iosfwd>
#include <utility>
#include <fcppt/config/external_end.hpp> // NOLINT(readability-duplicate-include)

sge::libpng::optional_file_rep sge::libpng::file_rep_from_stream(
    fcppt::log::object &_log, std::istream &_stream, sge::media::optional_name const &_name)
{
  sge::libpng::error_context error_context{fcppt::make_ref(_log), sge::media::optional_name{_name}};

  sge::libpng::read_ptr const read_ptr(fcppt::make_ref(error_context));

  sge::libpng::info const info(read_ptr.ptr());

  ::png_set_sig_bytes(read_ptr.ptr(), sge::libpng::header_bytes::value);

  sge::libpng::load_context const load_context{_stream, sge::media::optional_name{_name}, read_ptr};

  ::png_read_info(read_ptr.ptr(), info.get());

  sge::image2d::dim const size(
      ::png_get_image_width(read_ptr.ptr(), info.get()),
      ::png_get_image_height(read_ptr.ptr(), info.get()));

  png_byte const channels(::png_get_channels(read_ptr.ptr(), info.get()));

  sge::libpng::bit_depth const bpp{::png_get_bit_depth(read_ptr.ptr(), info.get())};

  sge::libpng::color_type const color_type{::png_get_color_type(read_ptr.ptr(), info.get())};

  if ((bpp.get() % CHAR_BIT) != 0)
  {
    throw sge::image2d::file_exception(
        _name, FCPPT_TEXT("A png file has a bit depth that's not a multiple of a byte's size!"));
  }

  FCPPT_LOG_DEBUG(
      _log,
      fcppt::log::out << FCPPT_TEXT("png: dimensions: ") << size << FCPPT_TEXT(", bit depth: ")
                      << fcppt::cast::promote_int(bpp.get()) << FCPPT_TEXT(", channels: ")
                      << fcppt::cast::promote_int(channels))

  switch (color_type.get())
  {
  case PNG_COLOR_TYPE_PALETTE: // NOLINT(hicpp-signed-bitwise)
    FCPPT_LOG_INFO(
        _log,
        fcppt::log::out << sge::media::error_string(
            _name, FCPPT_TEXT("Palette images are not supported.")))

    return sge::libpng::optional_file_rep();
  case PNG_COLOR_TYPE_GRAY:
    if (bpp.get() < 8 // NOLINT(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
    )
    {
      ::png_set_expand_gray_1_2_4_to_8(read_ptr.ptr());
    }
    break;
  default:
    break;
  }

  if (::png_get_valid(read_ptr.ptr(), info.get(), PNG_INFO_tRNS) != 0)
  {
    ::png_set_tRNS_to_alpha(read_ptr.ptr());
  }

  if (bpp.get() == 16 // NOLINT(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
  )
  {
    ::png_set_strip_16(read_ptr.ptr());
  }

  sge::libpng::bytes_per_pixel const bytes_per_pixel(
      fcppt::cast::to_unsigned((bpp.get() / CHAR_BIT) * channels));

  sge::libpng::byte_vector bytes(fcppt::container::buffer::to_raw_vector(
      fcppt::container::buffer::read_from<
          fcppt::container::buffer::object<sge::libpng::byte_vector::value_type>>(
          fcppt::math::dim::contents(size) * bytes_per_pixel.get(),
          [&read_ptr, bytes_per_pixel, size](
              sge::libpng::byte_vector::pointer const _data,
              sge::libpng::byte_vector::size_type const _byte_size)
          {
            sge::libpng::row_vector row_ptrs(
                sge::libpng::make_row_vector(size, _data, bytes_per_pixel));

            ::png_read_image(read_ptr.ptr(), row_ptrs.data());

            return _byte_size;
          })));

  return fcppt::optional::maybe(
      sge::libpng::make_format(_log, color_type, bpp, sge::libpng::get_gamma(read_ptr, info)),
      [&_log, &_name, bpp]
      {
        FCPPT_LOG_INFO(
            _log,
            fcppt::log::out << sge::media::error_string(
                                   _name, FCPPT_TEXT("Unsupported bits per pixel."))
                            << FCPPT_TEXT(" Depth is ") << fcppt::cast::promote_int(bpp.get()))

        return sge::libpng::optional_file_rep();
      },
      [size, &bytes](sge::libpng::format const _format) {
        return sge::libpng::optional_file_rep{
            sge::libpng::file_rep{size, _format, std::move(bytes)}};
      });
}
