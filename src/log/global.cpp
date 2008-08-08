#include <sge/char.hpp>
#include <sge/once.hpp>
#include <sge/log/global.hpp> 
#include <sge/log/logger.hpp>
#include <boost/iostreams/stream.hpp>
#include <boost/iostreams/device/null.hpp>

namespace
{
boost::iostreams::stream_buffer<
  boost::iostreams::basic_null_sink<
    sge::char_type
  >
> null_sink;

sge::log::logger_stream null_stream(&null_sink);

void initialize_sge_logger() {
  SGE_FUNCTION_ONCE
  sge::log::sge_logger()->writer().write(
    "%time%($hh:$mm.$ss.$mili)[%idx%]: ",
    "cerr"
  );
  sge::log::sge_logger()->mark_as_initialized();
  sge::log::sge_log_level()->set_enabled(sge::log::level::warning);
}

}

sge::log::logger_stream&
sge::log::global(const sge::log::level::type lvl)
{
  if(!sge_log_level()->is_enabled(lvl))
    return null_stream;
  return
    ::boost::logging::get_logger_base(sge_logger())->
      read_msg().gather().out();
}

