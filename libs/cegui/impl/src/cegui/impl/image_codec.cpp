//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/cegui/exception.hpp>
#include <sge/cegui/impl/image_codec.hpp>
#include <sge/cegui/impl/texture.hpp>
#include <sge/image2d/file.hpp>
#include <sge/image2d/load_raw_exn.hpp>
#include <sge/image2d/system_ref.hpp>
#include <sge/image2d/view/const_object.hpp>
#include <sge/media/const_raw_range.hpp>
#include <sge/media/optional_extension.hpp>
#include <fcppt/text.hpp>
#include <fcppt/optional/object_impl.hpp>
#include <fcppt/preprocessor/ignore_unsafe_buffer_usage.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>
#include <fcppt/config/external_begin.hpp>
#include <CEGUI/ImageCodec.h>
#include <CEGUI/Texture.h>
#include <fcppt/config/external_end.hpp>

sge::cegui::impl::image_codec::image_codec(sge::image2d::system_ref const _image_system)
    : CEGUI::ImageCodec("sge image codec"), image_system_(_image_system)
{
}

sge::cegui::impl::image_codec::~image_codec() = default;

FCPPT_PP_PUSH_WARNING
FCPPT_PP_IGNORE_UNSAFE_BUFFER_USAGE

CEGUI::Texture *sge::cegui::impl::image_codec::load(
    CEGUI::RawDataContainer const &_data, CEGUI::Texture *const _result_texture)
{
  if (_result_texture == nullptr)
  {
    throw sge::cegui::exception{FCPPT_TEXT("image_codec::load with nullptr")};
  }

  dynamic_cast<sge::cegui::impl::texture &>(*_result_texture)
      .create_from_view(
          sge::image2d::load_raw_exn(
              image_system_,
              sge::media::const_raw_range(
                  _data.getDataPtr(),
                  _data.getDataPtr() + // NOLINT(cppcoreguidelines-pro-bounds-pointer-arithmetic)
                      _data.getSize()
                  ),
              sge::media::optional_extension())
              ->view());

  return _result_texture;
}

FCPPT_PP_POP_WARNING

sge::image2d::system &sge::cegui::impl::image_codec::image_system() const
{
  return image_system_.get();
}
