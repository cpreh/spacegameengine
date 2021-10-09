//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/config/exception.hpp>
#include <sge/config/getenv.hpp>
#include <fcppt/optional_string.hpp>
#include <fcppt/string.hpp>
#include <fcppt/config/platform.hpp>
#if defined(FCPPT_CONFIG_WINDOWS_PLATFORM)
#include <sge/core/impl/include_windows.hpp>
#include <fcppt/char_type.hpp>
#include <fcppt/cast/size.hpp>
#include <fcppt/container/buffer/object_impl.hpp>
#include <fcppt/container/buffer/read_from_opt.hpp>
#include <fcppt/optional/make_if.hpp>
#include <fcppt/optional/map.hpp>
#else
#include <fcppt/from_std_string.hpp>
#include <fcppt/text.hpp>
#include <fcppt/to_std_string.hpp>
#include <fcppt/optional/to_exception.hpp>
#include <fcppt/config/external_begin.hpp>
#include <cstdlib>
#include <fcppt/config/external_end.hpp>
#endif

fcppt::optional_string sge::config::getenv(fcppt::string const &_name)
{
#if defined(FCPPT_CONFIG_WINDOWS_PLATFORM)
  typedef fcppt::container::buffer::object<fcppt::char_type> buffer_type;

  return fcppt::optional::map(
      fcppt::container::buffer::read_from_opt<buffer_type>(
          // An environment variable cannot be longer than 32767 characters
          32767u,
          [&_name](buffer_type::pointer const _data, buffer_type::size_type const _size)
          {
            DWORD const ret(
                ::GetEnvironmentVariable(_name.c_str(), _data, fcppt::cast::size<DWORD>(_size)));

            return fcppt::optional::make_if(
                ret != 0u, [ret] { return fcppt::cast::size<buffer_type::size_type>(ret); });
          }),
      [](fcppt::container::buffer::object<fcppt::char_type> &&_buffer)
      { return fcppt::string{_buffer.read_data()}; });
#else
  char const *const ret{
      ::std::getenv(fcppt::optional::to_exception(
                        fcppt::to_std_string(_name),
                        [&_name] {
                          return sge::config::exception{
                              FCPPT_TEXT("Failed to convert config variable name: ") + _name};
                        })
                        .c_str())};

  return ret != nullptr ? fcppt::optional_string(fcppt::from_std_string(ret))
                        : fcppt::optional_string();
#endif
}
