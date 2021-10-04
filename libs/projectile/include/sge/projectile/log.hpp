//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_PROJECTILE_LOG_HPP_INCLUDED
#define SGE_PROJECTILE_LOG_HPP_INCLUDED

#include <sge/projectile/log_fwd.hpp>
#include <sge/projectile/detail/symbol.hpp>
#include <fcppt/nonmovable.hpp>
#include <fcppt/log/context_reference_fwd.hpp>
#include <fcppt/log/object.hpp>


namespace sge::projectile
{

class log
{
	FCPPT_NONMOVABLE(
		log
	);
public:
	SGE_PROJECTILE_DETAIL_SYMBOL
	explicit
	log(
		fcppt::log::context_reference
	);

	SGE_PROJECTILE_DETAIL_SYMBOL
	~log();

	fcppt::log::object &
	world_log() const;

	fcppt::log::object &
	body_log() const;

	fcppt::log::object &
	ghost_log() const;

	fcppt::log::object &
	triangle_log() const;
private:
	mutable fcppt::log::object world_log_;

	mutable fcppt::log::object body_log_;

	mutable fcppt::log::object ghost_log_;

	mutable fcppt::log::object triangle_log_;
};

}

#endif
