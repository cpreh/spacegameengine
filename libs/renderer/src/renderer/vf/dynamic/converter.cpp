//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/renderer/exception.hpp>
#include <sge/renderer/impl/vf/dynamic/lock_interval.hpp>
#include <sge/renderer/impl/vf/dynamic/locked_part_interval.hpp>
#include <sge/renderer/impl/vf/dynamic/detail/converter_impl.hpp>
#include <sge/renderer/lock_flags/read.hpp>
#include <sge/renderer/lock_flags/write.hpp>
#include <sge/renderer/vf/dynamic/color_format_vector.hpp>
#include <sge/renderer/vf/dynamic/const_part_ref.hpp>
#include <sge/renderer/vf/dynamic/converter.hpp>
#include <sge/renderer/vf/dynamic/locked_part.hpp>
#include <sge/renderer/vf/dynamic/part.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/text.hpp>
#include <fcppt/optional/get_or_assign.hpp>
#include <fcppt/optional/maybe_void.hpp>
#include <fcppt/optional/object_impl.hpp>
#include <fcppt/optional/to_exception.hpp>
#include <fcppt/preprocessor/ignore_dangling_reference.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>
#include <fcppt/config/external_begin.hpp>
#include <utility>
#include <fcppt/config/external_end.hpp>

sge::renderer::vf::dynamic::converter::converter(
    sge::renderer::vf::dynamic::const_part_ref const _part,
    sge::renderer::vf::dynamic::color_format_vector &&_accepted_formats)
    : part_(_part),
      accepted_formats_(std::move(_accepted_formats)),
      written_intervals_(),
      locked_part_(),
      converter_()
{
}

sge::renderer::vf::dynamic::converter::~converter() = default;

void sge::renderer::vf::dynamic::converter::lock(
    sge::renderer::vf::dynamic::locked_part const &_locked_part)
{
  if (locked_part_.has_value())
  {
    throw sge::renderer::exception{FCPPT_TEXT("vf::dynamic::converter: Already locked!")};
  }

  if (sge::renderer::lock_flags::read(_locked_part.lock_flags()))
  {
    fcppt::optional::maybe_void(
        converter_,
        [&_locked_part, this](converter_unique_ptr const &_converter)
        {
          _converter->convert_lock(
              _locked_part.data(),
              _locked_part.pos(),
              written_intervals_,
              sge::renderer::impl::vf::dynamic::locked_part_interval(_locked_part));
        });
  }

  locked_part_ = optional_locked_part(_locked_part);
}

void sge::renderer::vf::dynamic::converter::unlock()
{
  sge::renderer::vf::dynamic::locked_part const &cur_locked_part{fcppt::optional::to_exception(
      this->locked_part_,
      [] { return sge::renderer::exception{FCPPT_TEXT("vf::dynamic::converter: Not locked!")}; })};

  FCPPT_PP_PUSH_WARNING
  FCPPT_PP_IGNORE_DANGLING_REFERENCE
  converter_unique_ptr const &conv{fcppt::optional::get_or_assign(
      this->converter_,
      [this]
      {
        return fcppt::make_unique_ptr<sge::renderer::vf::dynamic::detail::converter_impl>(
            this->part_.get(), this->accepted_formats_);
      })};
  FCPPT_PP_POP_WARNING

  if (sge::renderer::lock_flags::write(cur_locked_part.lock_flags()))
  {
    sge::renderer::impl::vf::dynamic::lock_interval const current_unlock(
        sge::renderer::impl::vf::dynamic::locked_part_interval(cur_locked_part));

    conv->convert_unlock(cur_locked_part.data(), cur_locked_part.pos(), current_unlock);

    written_intervals_.insert(current_unlock);
  }

  locked_part_ = optional_locked_part();
}

void sge::renderer::vf::dynamic::converter::reset()
{
  locked_part_ = optional_locked_part();

  written_intervals_.clear();
}
