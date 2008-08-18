#include <sge/char.hpp>
#include <sge/once.hpp>
#include <sge/text.hpp>
#include <sge/log/global.hpp> 
#include <sge/log/logger.hpp>
#include <boost/iostreams/stream_buffer.hpp>
#include <boost/iostreams/device/null.hpp>

namespace
{

BOOST_DECLARE_LOG_FILTER(
  sge_log_level,
  boost::logging::level::holder
)

BOOST_DEFINE_LOG_FILTER(
  sge_log_level, 
  boost::logging::level::holder
)

BOOST_DECLARE_LOG(
  sge_logger,
  sge::log::logger_type
)

BOOST_DEFINE_LOG(
  sge_logger, 
  sge::log::logger_type
)

void initialize_logger() {
  SGE_FUNCTION_ONCE
  sge_logger()->writer().write(
    SGE_TEXT("[%idx%] %time%($hh:$mm.$ss): "),
    SGE_TEXT("cerr")
  );
  sge_logger()->mark_as_initialized();
  sge_log_level()->set_enabled(
    sge::log::convert_level(
      sge::log::level::warning
    )
  );
}

}

sge::log::temporary_output::temporary_output()
  : os(new std::ostringstream())
{}

void sge::log::log(level::type const l, temporary_output const t) {
  initialize_logger();
  boost::logging::level::type bl = convert_level(l);
  if(sge_log_level()->is_enabled(bl))
    ::boost::logging::get_logger_base(
      sge_logger()
    )->read_msg().gather().out() << t.os->rdbuf();
}

