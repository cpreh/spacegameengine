#ifndef SGE_OPENAL_CONTEXT_WRAPPER_HPP_INCLUDED
#define SGE_OPENAL_CONTEXT_WRAPPER_HPP_INCLUDED

#include "openal.hpp"
#include <boost/noncopyable.hpp>
#include <vector>
#include <utility>

namespace sge
{
namespace openal
{
class device_wrapper;

class context_wrapper : boost::noncopyable
{
	public:
	typedef std::vector< std::pair<ALCint,ALCint> > attribute_container;
	context_wrapper(device_wrapper &,attribute_container const & = attribute_container());
	ALCcontext *context();
	void make_current();
	~context_wrapper();
	private:
	ALCcontext *context_;
};
}
}

#endif
