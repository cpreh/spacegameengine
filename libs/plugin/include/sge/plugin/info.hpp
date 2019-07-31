//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_PLUGIN_INFO_HPP_INCLUDED
#define SGE_PLUGIN_INFO_HPP_INCLUDED

#include <sge/plugin/capabilities_field.hpp>
#include <sge/plugin/description.hpp>
#include <sge/plugin/flags_field.hpp>
#include <sge/plugin/info_fwd.hpp>
#include <sge/plugin/min_core_version.hpp>
#include <sge/plugin/name.hpp>
#include <sge/plugin/version.hpp>
#include <sge/plugin/detail/symbol.hpp>


namespace sge
{
namespace plugin
{

class info
{
public:
	SGE_PLUGIN_DETAIL_SYMBOL
	info(
		sge::plugin::name &&,
		sge::plugin::description &&,
		sge::plugin::version,
		sge::plugin::min_core_version,
		sge::plugin::capabilities_field const &,
		sge::plugin::flags_field const &
	);

	SGE_PLUGIN_DETAIL_SYMBOL
	sge::plugin::name const &
	name() const;

	SGE_PLUGIN_DETAIL_SYMBOL
	sge::plugin::description const &
	description() const;

	SGE_PLUGIN_DETAIL_SYMBOL
	sge::plugin::version
	version() const;

	SGE_PLUGIN_DETAIL_SYMBOL
	sge::plugin::min_core_version
	min_core_version() const;

	SGE_PLUGIN_DETAIL_SYMBOL
	sge::plugin::capabilities_field const &
	capabilities() const;

	SGE_PLUGIN_DETAIL_SYMBOL
	sge::plugin::flags_field const &
	flags() const;
private:
	sge::plugin::name name_;

	sge::plugin::description description_;

	sge::plugin::version version_;

	sge::plugin::min_core_version min_core_version_;

	sge::plugin::capabilities_field capabilities_;

	sge::plugin::flags_field flags_;
};

}
}

#endif
