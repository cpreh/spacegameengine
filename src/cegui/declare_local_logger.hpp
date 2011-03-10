#ifndef SGEGUI_SRC_DECLARE_LOCAL_LOGGER_HPP_INCLUDED
#define SGEGUI_SRC_DECLARE_LOCAL_LOGGER_HPP_INCLUDED

#include <sge/cegui/logger.hpp>
#include <fcppt/log/object.hpp>
#include <fcppt/log/output.hpp>
#include <fcppt/log/macros.hpp>
#include <fcppt/log/parameters/inherited.hpp>

#define SGE_CEGUI_DECLARE_LOCAL_LOGGER(name)\
	namespace { fcppt::log::object local_log(fcppt::log::parameters::inherited(sge::cegui::logger(),name)); }

#endif
