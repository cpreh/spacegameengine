#include "log.hpp"
#include <sge/log/global.hpp>
#include <sge/text.hpp>

sge::log::logger &sge::gui::canvas::global_log()
{
  static logger global(sge::gui::global_log(),SGE_TEXT("canvas"),true);
  global.activate(log::level::debug);
  global.activate(log::level::info);
  global.activate(log::level::warning);
  global.activate(log::level::error);
  global.activate(log::level::fatal);
  return global;
}
