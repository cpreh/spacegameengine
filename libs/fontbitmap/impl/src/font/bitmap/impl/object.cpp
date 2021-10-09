//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/font/exception.hpp>
#include <sge/font/height.hpp>
#include <sge/font/log_location.hpp>
#include <sge/font/metrics.hpp>
#include <sge/font/string.hpp>
#include <sge/font/text.hpp>
#include <sge/font/text_parameters_fwd.hpp>
#include <sge/font/text_unique_ptr.hpp>
#include <sge/font/bitmap/impl/char_map.hpp>
#include <sge/font/bitmap/impl/char_metric.hpp>
#include <sge/font/bitmap/impl/double_insert.hpp>
#include <sge/font/bitmap/impl/load_one_file.hpp>
#include <sge/font/bitmap/impl/log_name.hpp>
#include <sge/font/bitmap/impl/object.hpp>
#include <sge/font/bitmap/impl/text.hpp>
#include <sge/image/color/format.hpp>
#include <sge/image/color/format_to_string.hpp>
#include <sge/image/color/optional_format.hpp>
#include <sge/image2d/file.hpp>
#include <sge/image2d/file_unique_ptr.hpp>
#include <sge/image2d/system_ref.hpp>
#include <sge/image2d/view/format.hpp>
#include <sge/log/default_parameters.hpp>
#include <sge/parse/json/array.hpp>
#include <sge/parse/json/find_member_exn.hpp>
#include <sge/parse/json/find_member_value_exn.hpp>
#include <sge/parse/json/get_exn.hpp>
#include <sge/parse/json/object.hpp>
#include <sge/parse/json/parse_file_exn.hpp>
#include <sge/parse/json/start.hpp>
#include <sge/parse/json/value.hpp>
#include <sge/parse/json/convert/to_int.hpp>
#include <fcppt/make_cref.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/recursive_impl.hpp>
#include <fcppt/text.hpp>
#include <fcppt/unique_ptr_to_base.hpp>
#include <fcppt/algorithm/fold.hpp>
#include <fcppt/log/context_reference.hpp>
#include <fcppt/optional/maybe_void.hpp>
#include <fcppt/config/external_begin.hpp>
#include <filesystem>
#include <utility>
#include <fcppt/config/external_end.hpp>

sge::font::bitmap::impl::object::object(
    fcppt::log::context_reference const _log_context,
    std::filesystem::path const &_path,
    sge::image2d::system_ref const _image_system)
    : object(_log_context, _path, _image_system, sge::parse::json::parse_file_exn(_path))
{
}

sge::font::bitmap::impl::object::~object() = default;

sge::font::bitmap::impl::object::object(
    fcppt::log::context_reference const _log_context,
    std::filesystem::path const &_path,
    sge::image2d::system_ref const _image_system,
    sge::parse::json::start const &_start)
    : log_{_log_context, sge::font::log_location(), sge::log::default_parameters(sge::font::bitmap::impl::log_name())},
      line_height_(sge::parse::json::convert::to_int<sge::font::unit>(
          sge::parse::json::find_member_value_exn(
              fcppt::make_cref(_start.object().members), "line_height")
              .get())),
      impl_(fcppt::algorithm::fold(
          sge::parse::json::find_member_exn<sge::parse::json::array>(
              fcppt::make_cref(_start.object().members), "textures")
              .get()
              .elements,
          std::make_pair(image_vector{}, sge::font::bitmap::impl::char_map{}),
          [&_path, &_image_system, this](
              fcppt::recursive<sge::parse::json::value> const &_element,
              std::pair<image_vector, sge::font::bitmap::impl::char_map> &&_state)
          {
            std::pair<sge::image2d::file_unique_ptr, sge::font::bitmap::impl::char_map> cur_file{
                sge::font::bitmap::impl::load_one_file(
                    log_,
                    _path.parent_path(),
                    sge::parse::json::get_exn<sge::parse::json::object>(
                        fcppt::make_cref(_element.get()))
                        .get(),
                    _image_system)};

            _state.first.push_back(std::move(cur_file.first));

            for (sge::font::bitmap::impl::char_map::value_type &element : cur_file.second)
            {
              if (_state.second.insert(std::make_pair(element.first, std::move(element.second)))
                      .second)
              {
                throw sge::font::bitmap::impl::double_insert(element.first);
              }
            }

            return std::move(_state);
          })),
      color_format_(fcppt::algorithm::fold(
          impl_.first,
          sge::image::color::optional_format(),
          [](sge::image2d::file_unique_ptr const &_file,
             sge::image::color::optional_format const _state)
          {
            sge::image::color::format const current_format(
                sge::image2d::view::format(_file->view()));

            fcppt::optional::maybe_void(
                _state,
                [current_format](sge::image::color::format const _last_format)
                {
                  if (_last_format != current_format)
                  {
                    throw sge::font::exception{
                        FCPPT_TEXT("Bitmapfont images can't differ in color formats! ")
                            FCPPT_TEXT(" The color formats are: ") +
                        sge::image::color::format_to_string(_last_format) + FCPPT_TEXT(" and ") +
                        sge::image::color::format_to_string(current_format)};
                  }
                });

            return sge::image::color::optional_format(current_format);
          }))
{
}

sge::font::text_unique_ptr sge::font::bitmap::impl::object::create_text(
    sge::font::string const &_string, sge::font::text_parameters const &_text_parameters)
{
  return fcppt::unique_ptr_to_base<sge::font::text>(
      fcppt::make_unique_ptr<sge::font::bitmap::impl::text>(
          log_, impl_.second, _string, _text_parameters, line_height_));
}

sge::image::color::optional_format sge::font::bitmap::impl::object::preferred_color_format() const
{
  return color_format_;
}

sge::font::metrics sge::font::bitmap::impl::object::metrics() const
{
  return sge::font::metrics(sge::font::height(line_height_.get()));
}
