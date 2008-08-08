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
    "[%idx%] %time%($hh:$mm.$ss): ",
    "cerr"
  );
  sge::log::sge_logger()->mark_as_initialized();
  //sge::log::sge_log_level()->set_enabled(sge::log::level::warning);
}

}

sge::log::logger_stream&
sge::log::global(const sge::log::level::type lvl)
{
  initialize_sge_logger();
  const bool use_logger(sge_log_level()->is_enabled(lvl));
//  if(!sge_log_level()->is_enabled(lvl))
  if(!use_logger)
    return null_stream;
  return null_stream;
  /*
    ::boost::logging::get_logger_base(sge_logger())->
      read_msg().gather().out();
  */
}

