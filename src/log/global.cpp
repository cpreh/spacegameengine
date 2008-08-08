#include <sge/char.hpp>
#include <sge/once.hpp>
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

BOOST_DECLARE_LOG(
  sge_logger, 
  sge::log::logger_type
)

BOOST_DEFINE_LOG(
  sge_logger, 
  sge::log::logger_type
)

BOOST_DEFINE_LOG_FILTER(
  sge_log_level, 
  boost::logging::level::holder
)

typedef boost::iostreams::basic_null_sink<
  sge::char_type
> null_sink_type;

//null_sink_type null_sink;

boost::iostreams::stream_buffer<
  null_sink_type
> null_stream_buffer;

sge::log::logger_stream null_stream(
  &null_stream_buffer);

void initialize_sge_logger() {
  SGE_FUNCTION_ONCE
  sge_logger()->writer().write(
    "[%idx%] %time%($hh:$mm.$ss): ",
    "cerr"
  );
  sge_logger()->mark_as_initialized();
  sge_log_level()->set_enabled(sge::log::level::warning);
}

}

sge::log::logger_stream&
sge::log::global(const sge::log::level::type lvl)
{
  initialize_sge_logger();
//  const bool use_logger(sge_log_level()->is_enabled(lvl));
  const bool use_logger(true);
//  if(!sge_log_level()->is_enabled(lvl))
  return use_logger
  ?  ::boost::logging::get_logger_base(
       sge_logger())->
         read_msg().gather().out()
  : null_stream;
}

