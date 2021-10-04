//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_SYSTEMS_IMPL_FONT_OBJECT_HPP_INCLUDED
#define SGE_SYSTEMS_IMPL_FONT_OBJECT_HPP_INCLUDED

#include <sge/font/system_fwd.hpp>
#include <sge/font/system_unique_ptr.hpp>
#include <sge/font/plugin/collection_fwd.hpp>
#include <sge/font/plugin/object.hpp>
#include <sge/systems/font_fwd.hpp>
#include <sge/systems/impl/font/object_fwd.hpp>
#include <fcppt/nonmovable.hpp>
#include <fcppt/log/context_reference_fwd.hpp>


namespace sge::systems::impl::font
{

class object
{
	FCPPT_NONMOVABLE(
		object
	);
public:
	object(
		fcppt::log::context_reference,
		sge::font::plugin::collection const &,
		sge::systems::font const &
	);

	~object();

	[[nodiscard]]
	sge::font::system &
	system() const;
private:
	sge::font::plugin::object const font_plugin_;

	sge::font::system_unique_ptr const font_system_;
};

}

#endif
