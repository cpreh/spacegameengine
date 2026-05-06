//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/parse/ini/typed/duplicate_entry.hpp>
#include <sge/parse/ini/typed/duplicate_section.hpp>
#include <sge/parse/ini/typed/entry_error.hpp>
#include <sge/parse/ini/typed/entry_type_error.hpp>
#include <sge/parse/ini/typed/missing_entry_error.hpp>
#include <sge/parse/ini/typed/missing_section_error.hpp>
#include <sge/parse/ini/typed/section_error.hpp>
#include <sge/parse/ini/typed/section_start_error.hpp>
#include <sge/parse/ini/typed/start_error.hpp>
#include <sge/parse/ini/typed/start_error_output.hpp>
#include <fcppt/output.hpp>
#include <fcppt/output_string.hpp> // IWYU pragma: keep
#include <fcppt/strong_typedef_output.hpp> // IWYU pragma: keep
#include <fcppt/text.hpp>
#include <fcppt/type_name_from_index.hpp>
#include <fcppt/container/output.hpp>
#include <fcppt/io/ostream.hpp>
#include <fcppt/variant/match.hpp>
#include <fcppt/config/external_begin.hpp>
#include <vector>
#include <fcppt/config/external_end.hpp>

fcppt::io::ostream &sge::parse::ini::typed::operator<<(
    fcppt::io::ostream &_stream, sge::parse::ini::typed::start_error const &_error)
{
  fcppt::variant::match(
      _error.variant_,
      [&_stream](std::vector<sge::parse::ini::typed::duplicate_section> const &_dup_section)
      {
        _stream << FCPPT_TEXT("Duplicate section names \"") << fcppt::container::output(_dup_section)
                << FCPPT_TEXT('"');
      },
      [&_stream](
          std::vector<sge::parse::ini::typed::section_start_error> const &_section_start_errors)
      {
        for (sge::parse::ini::typed::section_start_error const &start_error : _section_start_errors)
        {
          fcppt::variant::match(
              start_error.variant_,
              [&_stream](sge::parse::ini::typed::section_error const &_section_error)
              {
                _stream << FCPPT_TEXT("In section ") << fcppt::output(_section_error.name_)
                        << FCPPT_TEXT(": ");

                fcppt::variant::match(
                    _section_error.variant_,
                    [&_stream](
                        std::vector<sge::parse::ini::typed::duplicate_entry> const &_dup_entry)
                    {
                      _stream << FCPPT_TEXT("Duplicate entries \"")
                              << fcppt::container::output(_dup_entry) << FCPPT_TEXT('"');
                    },
                    [&_stream](std::vector<sge::parse::ini::typed::entry_error> const &_entry_errors)
                    {
                      for(sge::parse::ini::typed::entry_error const &_entry_error : _entry_errors)
                      {
                        fcppt::variant::match(
                            _entry_error.variant_,
                            [&_stream](sge::parse::ini::typed::entry_type_error const &_type_error)
                            {
                              _stream
                                  << FCPPT_TEXT("Failed to convert \"")
                                  << fcppt::output(_type_error.value) << FCPPT_TEXT("\" to type ")
                                  << fcppt::output(fcppt::type_name_from_index(_type_error.type))
                                  << FCPPT_TEXT(" for entry \"") << fcppt::output(_type_error.name)
                                  << FCPPT_TEXT("\".");
                            },
                            [&_stream](
                                sge::parse::ini::typed::missing_entry_error const &_missing_error)
                            {
                              _stream << FCPPT_TEXT("Missing entry \"")
                                      << fcppt::output(_missing_error) << FCPPT_TEXT("\".");
                            });
                        _stream << FCPPT_TEXT('\n');
                      }
                    });
              },
              [&_stream](
                  sge::parse::ini::typed::missing_section_error const &_missing_section_error)
              {
                _stream << FCPPT_TEXT("Missing section \"") << _missing_section_error
                        << FCPPT_TEXT("\".");
              });

          _stream << FCPPT_TEXT('\n');
        }
      });

  return _stream;
}
