#ifndef SGE_OPENAL_CONTEXT_HPP_INCLUDED
#define SGE_OPENAL_CONTEXT_HPP_INCLUDED

#include "openal.hpp"
#include <boost/noncopyable.hpp>
#include <vector>
#include <utility>

namespace sge
{
namespace openal
{
class device;

class context : boost::noncopyable
{
	public:
	typedef std::vector< std::pair<ALCint,ALCint> > attribute_container;
	context(device &,attribute_container const & = attribute_container());
	ALCcontext *alcontext() { return context_; }
	void make_current();
	~context();
	private:
	ALCcontext *context_;
	device &device_;
};
}
}

#endif
