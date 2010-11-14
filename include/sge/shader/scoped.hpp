#ifndef SGE_SHADER_SCOPED_HPP_INCLUDED
#define SGE_SHADER_SCOPED_HPP_INCLUDED

#include <sge/shader/object_fwd.hpp>

namespace sge
{
namespace shader
{
class scoped
{
public:
	scoped(scoped const &) = delete;
	scoped &operator=(scoped const &) = delete;
	
	explicit
	scoped(
		object &);

	~scoped();
private:
	object &object_;
};
}
}

#endif
