//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_PLUGIN_CONTEXT_HPP_INCLUDED
#define SGE_PLUGIN_CONTEXT_HPP_INCLUDED

#include <sge/plugin/context_base_fwd.hpp>
#include <sge/plugin/context_fwd.hpp>
#include <sge/plugin/info_fwd.hpp>
#include <sge/plugin/object_fwd.hpp>
#include <sge/plugin/detail/instantiate/symbol.hpp>
#include <fcppt/reference_decl.hpp>
#include <fcppt/config/external_begin.hpp>
#include <filesystem>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace plugin
{

template<
	typename Type
>
class context
{
public:
	SGE_PLUGIN_DETAIL_INSTANTIATE_SYMBOL
	explicit
	context(
		sge::plugin::context_base &
	);

	SGE_PLUGIN_DETAIL_INSTANTIATE_SYMBOL
	context(
		context const &
	);

	SGE_PLUGIN_DETAIL_INSTANTIATE_SYMBOL
	context &
	operator=(
		context const &
	);

	SGE_PLUGIN_DETAIL_INSTANTIATE_SYMBOL
	~context();

	typedef
	sge::plugin::object<
		Type
	>
	object;

	SGE_PLUGIN_DETAIL_INSTANTIATE_SYMBOL
	object
	load() const;

	SGE_PLUGIN_DETAIL_INSTANTIATE_SYMBOL
	std::filesystem::path const &
	path() const;

	SGE_PLUGIN_DETAIL_INSTANTIATE_SYMBOL
	sge::plugin::info const &
	info() const;
private:
	fcppt::reference<
		sge::plugin::context_base
	> context_base_;
};

}
}

#endif
