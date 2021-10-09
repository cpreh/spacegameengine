//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/image2d/file_exception.hpp>
#include <sge/libpng/error_context.hpp>
#include <sge/libpng/png.hpp>
#include <sge/media/error_string.hpp>
#include <sge/media/optional_name.hpp>
#include <fcppt/from_std_string.hpp>
#include <fcppt/text.hpp>
#include <fcppt/cast/from_void_ptr.hpp>
#include <fcppt/log/object_reference.hpp>
#include <fcppt/log/out.hpp>
#include <fcppt/log/warning.hpp>
#include <fcppt/preprocessor/disable_clang_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>
#include <fcppt/config/external_begin.hpp>
#include <utility>
#include <fcppt/config/external_end.hpp>

sge::libpng::error_context::error_context(
    fcppt::log::object_reference const _log, sge::media::optional_name &&_name)
    : log_{_log}, name_(std::move(_name))
{
}

sge::libpng::error_context::~error_context() = default;

void sge::libpng::error_context::handle_warning(
    png_structp const _read_ptr, // NOLINT(misc-misplaced-const)
    png_const_charp const _data)
{
  sge::libpng::error_context::get_instance(_read_ptr).handle_warning_impl(_data);
}

FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_CLANG_WARNING(-Wmissing-noreturn)

void sge::libpng::error_context::handle_error(
    png_structp const _read_ptr, // NOLINT(misc-misplaced-const)
    png_const_charp const _data)
{
  sge::libpng::error_context::get_instance(_read_ptr).handle_error_impl(_data);
}

FCPPT_PP_POP_WARNING

void sge::libpng::error_context::handle_warning_impl(png_const_charp const _message)
{
  FCPPT_LOG_WARNING(
      log_.get(),
      fcppt::log::out << sge::media::error_string(name_, fcppt::from_std_string(_message)))
}

void sge::libpng::error_context::handle_error_impl(png_const_charp const _message)
{
  throw sge::image2d::file_exception(name_, fcppt::from_std_string(_message));
}

sge::libpng::error_context &
sge::libpng::error_context::get_instance(png_structp const _read_ptr // NOLINT(misc-misplaced-const)
)
{
  return *fcppt::cast::from_void_ptr<sge::libpng::error_context *>(::png_get_error_ptr(_read_ptr));
}
