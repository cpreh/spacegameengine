#ifndef SGE_OPENAL_CONTEXT_WRAPPER_HPP_INCLUDED
#define SGE_OPENAL_CONTEXT_WRAPPER_HPP_INCLUDED

class ALCcontext;

namespace sge
{
namespace openal
{
class device_wrapper;

class context_wrapper
{
	public:
	typedef std::vector< std::pair<ALCint,ALCint> > attribute_container;
	context_wrapper(device_wrapper &,attribute_container const & = attribute_container());
	ALCcontext *context();
	void make_current();
	~context_wrapper();
	private:
	ALCcontext * const context_;
};
}
}

#endif
