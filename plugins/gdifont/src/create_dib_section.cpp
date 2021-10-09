//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/font/exception.hpp>
#include <sge/gdifont/create_dib_section.hpp>
#include <sge/gdifont/delete_object_deleter.hpp>
#include <sge/gdifont/device_context.hpp>
#include <sge/gdifont/hbitmap_unique_ptr.hpp>
#include <sge/gdifont/include_windows.hpp>
#include <sge/image2d/dim.hpp>
#include <fcppt/text.hpp>
#include <fcppt/cast/size.hpp>
#include <fcppt/cast/to_signed.hpp>

sge::gdifont::hbitmap_unique_ptr sge::gdifont::create_dib_section(
    sge::gdifont::device_context const &_device_context,
    sge::image2d::dim const &_dim,
    VOID *&_bits_result)
{
  // TODO: Support all formats
  BITMAPINFO info;

  ZeroMemory(&info, sizeof(BITMAPINFO));

  BITMAPINFOHEADER &header(info.bmiHeader);

  header.biSize = fcppt::cast::size<DWORD>(sizeof(BITMAPINFOHEADER));

  header.biWidth = fcppt::cast::size<LONG>(fcppt::cast::to_signed(_dim.w()));

  // negative values indicate topdown bitmaps
  header.biHeight = -fcppt::cast::size<LONG>(fcppt::cast::to_signed(_dim.h()));

  header.biPlanes = 1;

  // TODO: Support more formats!
  header.biBitCount = 8;

  header.biCompression = BI_RGB;

  header.biSizeImage = 0;

  header.biXPelsPerMeter = 0; // TODO!

  header.biYPelsPerMeter = 0; // TODO!

  header.biClrUsed = 0;

  header.biClrImportant = 0;

  HBITMAP const result(
      ::CreateDIBSection(_device_context.get(), &info, DIB_RGB_COLORS, &_bits_result, nullptr, 0u));

  if (result == nullptr)
    throw sge::font::exception(FCPPT_TEXT("CreateDIBSection failed!"));

  return sge::gdifont::hbitmap_unique_ptr(result);
}
