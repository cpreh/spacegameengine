#include <sge/log/convert_level.hpp>
#include <sge/exception.hpp>
#include <sge/text.hpp>

boost::logging::level::type
sge::log::convert_level(level::type const lvl) {
  switch(lvl) {
    case  level::debug:
      return boost::logging::level::debug;
    case  level::info:
      return boost::logging::level::info;
    case  level::warning:
      return boost::logging::level::warning;
    case  level::error:
      return boost::logging::level::error;
    case  level::fatal:
      return boost::logging::level::fatal;
    default:
      throw exception(
        SGE_TEXT("sge::log::level::convert_level: unsupported log level type")
      );
  }
}
