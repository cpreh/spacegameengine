//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/parse/ini/entry_name.hpp>
#include <sge/parse/ini/optional_start.hpp>
#include <sge/parse/ini/start.hpp>
#include <sge/parse/ini/typed/entry.hpp>
#include <sge/parse/ini/typed/required.hpp>
#include <sge/parse/ini/typed/section.hpp>
#include <sge/parse/ini/typed/section_result.hpp>
#include <sge/parse/ini/typed/start.hpp>
#include <sge/parse/ini/typed/start_error.hpp>
#include <sge/parse/ini/typed/start_error_output.hpp> // IWYU pragma: keep
#include <sge/parse/ini/typed/start_result.hpp>
#include <sge/systems/optional_name.hpp>
#include <sge/systems/impl/ini_section_name.hpp>
#include <sge/systems/impl/parse_plugin_name.hpp>
#include <fcppt/copy.hpp>
#include <fcppt/from_std_string.hpp>
#include <fcppt/text.hpp>
#include <fcppt/either/match.hpp>
#include <fcppt/log/object_fwd.hpp>
#include <fcppt/log/out.hpp>
#include <fcppt/log/warning.hpp>
#include <fcppt/optional/bind.hpp>
#include <fcppt/optional/object_impl.hpp>
#include <fcppt/record/element.hpp>
#include <fcppt/record/get.hpp>
#include <fcppt/record/make.hpp>
#include <fcppt/record/make_label.hpp>
#include <fcppt/record/object_impl.hpp>
#include <fcppt/config/external_begin.hpp>
#include <string>
#include <fcppt/config/external_end.hpp>

sge::systems::optional_name sge::systems::impl::parse_plugin_name(
    fcppt::log::object &_log,
    sge::parse::ini::optional_start const &_opt_start,
    sge::parse::ini::entry_name const &_name)
{
  return fcppt::optional::bind(
      _opt_start,
      [&_name, &_log](sge::parse::ini::start const &_start) -> sge::systems::optional_name
      {
        FCPPT_RECORD_MAKE_LABEL(section_label);
        FCPPT_RECORD_MAKE_LABEL(entry_label);

        using section_type = sge::parse::ini::typed::section_result<fcppt::record::object<
            fcppt::record::element<entry_label, fcppt::optional::object<std::string>>>>;

        using result_type = sge::parse::ini::typed::start_result<fcppt::record::object<
            fcppt::record::element<section_label, fcppt::optional::object<section_type>>>>;

        sge::parse::ini::typed::start const parser{fcppt::record::make(
            section_label{} = sge::parse::ini::typed::section{
                fcppt::copy(sge::systems::impl::ini_section_name().get()),
                fcppt::record::make(
                    entry_label{} = sge::parse::ini::typed::
                        entry<std::string, sge::parse::ini::typed::required::no>{
                            fcppt::copy(_name.get())})})};

        return fcppt::either::match(
            parser.parse(_start),
            [&_log](
                sge::parse::ini::typed::start_error const &_error) -> sge::systems::optional_name
            {
              FCPPT_LOG_WARNING(
                  _log,
                  fcppt::log::out << FCPPT_TEXT("Error parsing plugin string: \"") << _error
                                  << FCPPT_TEXT(".\""))

              return sge::systems::optional_name{};
            },
            [](result_type const &_result) -> sge::systems::optional_name
            {
              return fcppt::optional::bind(
                  fcppt::record::get<section_label>(_result.result),
                  [](section_type const &_section) -> sge::systems::optional_name
                  {
                    return fcppt::optional::bind(
                        fcppt::record::get<entry_label>(_section.result),
                        [](std::string const &_value)
                        {
                          return sge::systems::optional_name{
                              sge::plugin::name{fcppt::from_std_string(_value)}};
                        });
                  });
            });
      });
}
