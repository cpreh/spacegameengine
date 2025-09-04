//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/plugin/impl/library/error.hpp>
#include <sge/plugin/impl/library/loaded_symbol.hpp>
#include <sge/plugin/impl/library/object.hpp>
#include <sge/plugin/library/exception.hpp>
#include <sge/plugin/library/symbol_string.hpp>
#include <fcppt/from_std_string.hpp>
#include <fcppt/string.hpp>
#include <fcppt/text.hpp>
#include <fcppt/config/platform.hpp>
#include <fcppt/filesystem/path_to_string.hpp>
#include <fcppt/optional/from.hpp>
#include <fcppt/config/external_begin.hpp>
#ifdef FCPPT_CONFIG_WINDOWS_PLATFORM
#include <exception>
#include <vector>
#elifdef FCPPT_CONFIG_POSIX_PLATFORM
#include <dlfcn.h>
#endif
#include <filesystem>
#include <utility>
#include <fcppt/config/external_end.hpp>

#ifdef FCPPT_CONFIG_WINDOWS_PLATFORM
#include <awl/backends/windows/windows.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/nonmovable.hpp>
#include <fcppt/unique_ptr_impl.hpp>
#elifdef FCPPT_CONFIG_POSIX_PLATFORM
#include <fcppt/optional/maybe_void.hpp>
#else
#error "Implement me!"
#endif

#ifdef FCPPT_CONFIG_WINDOWS_PLATFORM
namespace
{

void free_library(HMODULE const _handle) { ::FreeLibrary(_handle); }

struct context
{
  FCPPT_NONMOVABLE(context);

public:
  explicit context(HMODULE const _handle) : handle_(_handle) {}

  ~context() { free_library(handle_); }

private:
  HMODULE const handle_;
};

typedef fcppt::unique_ptr<context> context_unique_ptr;

typedef std::vector<context_unique_ptr> library_vector;

library_vector libraries;

}

struct sge::plugin::library::object::destroyer
{
  FCPPT_NONMOVABLE(destroyer);

public:
  destroyer() = default;

  ~destroyer() { libraries.clear(); }
};

#endif

sge::plugin::library::object::object(std::filesystem::path &&_name)
    : name_(std::move(_name)),
#ifdef FCPPT_CONFIG_WINDOWS_PLATFORM
      handle_(::LoadLibrary(fcppt::filesystem::path_to_string(name_).c_str())),
      destroyer_(fcppt::make_unique_ptr<destroyer>())
#elifdef FCPPT_CONFIG_POSIX_PLATFORM
      handle_(::dlopen(name_.string().c_str(), RTLD_NOW))
#endif
{
  if (handle_ == nullptr)
  {
    throw sge::plugin::library::exception{
        fcppt::string{FCPPT_TEXT("Failed to load library::object: ")} +
        fcppt::optional::from(
            sge::plugin::impl::library::error(),
            [] { return fcppt::string{FCPPT_TEXT("No error")}; })};
  }
}

sge::plugin::library::object::~object()
{
  if (handle_ == nullptr)
  {
    return;
  }

#ifdef FCPPT_CONFIG_WINDOWS_PLATFORM
  // NOTE: We can't free the library here,
  // because an exception might be propagating that
  // has been thrown from a DLL.
  // If we destroy the DLL here, the catch of
  // exception will crash.
  if (std::uncaught_exceptions() > 0)
  {
    libraries.push_back(fcppt::make_unique_ptr<context>(handle_));
  }
  else
  {
    free_library(handle_);
  }
#elifdef FCPPT_CONFIG_POSIX_PLATFORM
  ::dlclose(handle_);
#endif
}

std::filesystem::path const &sge::plugin::library::object::name() const { return name_; }

sge::plugin::impl::library::loaded_symbol
sge::plugin::library::object::load(sge::plugin::library::symbol_string const &_fun)
{
#ifdef FCPPT_CONFIG_WINDOWS_PLATFORM
  FARPROC const ret{::GetProcAddress(this->handle_, _fun.c_str())};

  if (ret == nullptr)
  {
    throw sge::plugin::library::exception{
        FCPPT_TEXT("Function ") + fcppt::from_std_string(_fun) + FCPPT_TEXT(" not found in ") +
        fcppt::filesystem::path_to_string(this->name())};
  };

  return ret;
#elifdef FCPPT_CONFIG_POSIX_PLATFORM
  // NOLINTNEXTLINE(concurrency-mt-unsafe)
  ::dlerror(); // clear last error

  // NOLINTNEXTLINE(misc-const-correctness)
  void *const ret{::dlsym(this->handle_, _fun.c_str())};

  fcppt::optional::maybe_void(
      sge::plugin::impl::library::error(),
      [&_fun, this] [[noreturn]] (fcppt::string &&_error)
      {
        throw sge::plugin::library::exception{
            fcppt::from_std_string(_fun) + FCPPT_TEXT(" not found in library ") +
            fcppt::filesystem::path_to_string(this->name()) + FCPPT_TEXT(": ") + std::move(_error)};
      });

  return ret;
#endif
}
