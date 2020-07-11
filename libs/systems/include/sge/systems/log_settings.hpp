//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_SYSTEMS_LOG_SETTINGS_HPP_INCLUDED
#define SGE_SYSTEMS_LOG_SETTINGS_HPP_INCLUDED

#include <sge/log/option_container.hpp>
#include <sge/systems/log_settings_fwd.hpp>
#include <sge/systems/optional_log_context_ref.hpp>
#include <sge/systems/detail/symbol.hpp>
#include <fcppt/log/context_reference_fwd.hpp>


namespace sge
{
namespace systems
{

class log_settings
{
public:
	SGE_SYSTEMS_DETAIL_SYMBOL
	explicit
	log_settings(
		sge::log::option_container &&
	);

	SGE_SYSTEMS_DETAIL_SYMBOL
	sge::systems::log_settings
	log_context(
		fcppt::log::context_reference
	) &&;

	[[nodiscard]]
	sge::log::option_container const &
	options() const;

	[[nodiscard]]
	sge::systems::optional_log_context_ref const &
	log_context() const;
private:
	sge::log::option_container options_;

	sge::systems::optional_log_context_ref log_context_;
};

}
}

#endif
