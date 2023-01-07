//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/opencl/exception.hpp>
#include <sge/opencl/platform/version.hpp>
#include <fcppt/from_std_string.hpp>
#include <fcppt/output_to_std_string.hpp>
#include <fcppt/text.hpp>
#include <fcppt/either/to_exception.hpp>
#include <fcppt/parse/char.hpp>
#include <fcppt/parse/literal.hpp>
#include <fcppt/parse/uint.hpp>
#include <fcppt/parse/parse_string.hpp>
#include <fcppt/parse/parse_string_error.hpp>
#include <fcppt/parse/parse_string_error_output.hpp>
#include <fcppt/parse/string.hpp>
#include <fcppt/parse/operators/repetition.hpp>
#include <fcppt/parse/operators/sequence.hpp>
#include <fcppt/tuple/get.hpp>
#include <fcppt/config/compiler.hpp>
#include <fcppt/config/external_begin.hpp>
#include <string>
#include <fcppt/config/external_end.hpp>

sge::opencl::platform::version::version(std::string const &_version_string)
    : info_{fcppt::either::to_exception(
          fcppt::parse::parse_string(
              fcppt::parse::string{"OpenCL "} >> fcppt::parse::uint<unit>{} >>
                  fcppt::parse::literal{'.'} >> fcppt::parse::uint<unit>{} >>
                  fcppt::parse::literal{' '} >> *fcppt::parse::char_{},
              std::string{_version_string}),
          [](fcppt::parse::parse_string_error<char> &&_error)
          {
            return sge::opencl::exception{
                FCPPT_TEXT("Failed to parse version: ") +
                fcppt::from_std_string(fcppt::output_to_std_string(_error))};
          })}
{
}

sge::opencl::platform::version::unit sge::opencl::platform::version::major_part() const
{
  return fcppt::tuple::get<0U>(this->info_);
}

sge::opencl::platform::version::unit sge::opencl::platform::version::minor_part() const
{
  return fcppt::tuple::get<1U>(this->info_);
}

std::string const &sge::opencl::platform::version::platform_specific() const
{
  return fcppt::tuple::get<2U>(this->info_);
}
