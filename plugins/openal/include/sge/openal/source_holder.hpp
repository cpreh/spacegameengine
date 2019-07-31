//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_OPENAL_SOURCE_HOLDER_HPP_INCLUDED
#define SGE_OPENAL_SOURCE_HOLDER_HPP_INCLUDED

#include <sge/openal/source_id.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/log/object_fwd.hpp>


namespace sge
{
namespace openal
{

class source_holder
{
	FCPPT_NONCOPYABLE(
		source_holder
	);
public:
	explicit
	source_holder(
		fcppt::log::object &
	);

	~source_holder();

	sge::openal::source_id
	get() const;
private:
	fcppt::log::object &log_;

	sge::openal::source_id const value_;
};

}
}

#endif
