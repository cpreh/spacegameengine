//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_SYSTEMS_IMPL_LOG_CONTEXT_HPP_INCLUDED
#define SGE_SYSTEMS_IMPL_LOG_CONTEXT_HPP_INCLUDED

#include <sge/systems/optional_log_context_ref_fwd.hpp>
#include <fcppt/nonmovable.hpp>
#include <fcppt/reference_impl.hpp>
#include <fcppt/unique_ptr_impl.hpp>
#include <fcppt/log/context_reference.hpp>
#include <fcppt/variant/object_impl.hpp>


namespace sge::systems::impl
{

class log_context
{
	FCPPT_NONMOVABLE(
		log_context
	);
public:
	explicit
	log_context(
		sge::systems::optional_log_context_ref
	);

	~log_context();

	[[nodiscard]]
	fcppt::log::context_reference
	get() const;
private:
	using
	variant
	=
	fcppt::variant::object<
		fcppt::unique_ptr<
			fcppt::log::context
		>,
		fcppt::reference<
			fcppt::log::context
		>
	>;

	variant const impl_;
};

}

#endif
