//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_OPENAL_CONTEXT_HPP_INCLUDED
#define SGE_OPENAL_CONTEXT_HPP_INCLUDED

#include <sge/openal/alc.hpp>
#include <sge/openal/context_fwd.hpp>
#include <sge/openal/device_fwd.hpp>
#include <fcppt/noncopyable.hpp>


namespace sge
{
namespace openal
{

class context
{
	FCPPT_NONCOPYABLE(
		context
	);
public:
	explicit
	context(
		sge::openal::device &
	);

	ALCcontext &
	alcontext();

	ALCdevice &
	aldevice();

	~context();
private:
	sge::openal::device &device_;

	ALCcontext *const context_;
};

}
}

#endif
