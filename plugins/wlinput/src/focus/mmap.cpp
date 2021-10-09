//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/input/exception.hpp>
#include <sge/wlinput/focus/mmap.hpp>
#include <awl/backends/posix/fd.hpp>
#include <fcppt/text.hpp>
#include <fcppt/assert/error.hpp>
#include <fcppt/cast/from_void_ptr.hpp>
#include <fcppt/config/external_begin.hpp>
#include <sys/mman.h>
#include <cstdint>
#include <fcppt/config/external_end.hpp>

sge::wlinput::focus::mmap::mmap(awl::backends::posix::fd const _fd, std::uint32_t const _size)
    : size_{_size},
      string_{fcppt::cast::from_void_ptr<char *>(
          ::mmap(nullptr, size_, PROT_READ, MAP_SHARED, _fd.get(), 0))}
{
  if (string_ == MAP_FAILED // NOLINT(cppcoreguidelines-pro-type-cstyle-cast)
  )
  {
    throw sge::input::exception{FCPPT_TEXT("Cannot map keymap")};
  }
}

sge::wlinput::focus::mmap::~mmap() { FCPPT_ASSERT_ERROR(::munmap(string_, size_) == 0); }

char const *sge::wlinput::focus::mmap::string() const { return string_; }
