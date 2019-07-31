//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_SYSTEMS_CONFIG_HPP_INCLUDED
#define SGE_SYSTEMS_CONFIG_HPP_INCLUDED

#include <sge/systems/config_fwd.hpp>
#include <sge/systems/log_settings.hpp>
#include <sge/systems/optional_log_settings.hpp>
#include <sge/systems/optional_plugin_path.hpp>
#include <sge/systems/detail/symbol.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/filesystem/path.hpp>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace systems
{

class config
{
public:
	SGE_SYSTEMS_DETAIL_SYMBOL
	config();

	SGE_SYSTEMS_DETAIL_SYMBOL
	sge::systems::config &
	plugin_path(
		boost::filesystem::path const &
	);

	SGE_SYSTEMS_DETAIL_SYMBOL
	sge::systems::config &
	log_settings(
		sge::systems::log_settings const &
	);

	sge::systems::optional_plugin_path const &
	plugin_path() const;

	sge::systems::optional_log_settings const &
	log_settings() const;
private:
	sge::systems::optional_plugin_path plugin_path_;

	sge::systems::optional_log_settings log_settings_;
};

}
}

#endif
