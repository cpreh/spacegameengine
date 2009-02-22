#ifndef SGE_CONSOLE_VAR_BASE_HPP_INCLUDED
#define SGE_CONSOLE_VAR_BASE_HPP_INCLUDED

#include <sge/console/object_fwd.hpp>
#include <sge/string.hpp>
#include <sge/export.hpp>
#include <sge/noncopyable.hpp>

namespace sge
{
namespace console
{
class SGE_CLASS_SYMBOL var_base
{
	SGE_NONCOPYABLE(var_base)
	public:
	SGE_SYMBOL var_base(
		object &,
		sge::string const &);
	
	virtual void string(sge::string const &) = 0;
	virtual sge::string const string() const = 0;

	SGE_SYMBOL sge::string const name() const;
	
	virtual ~var_base();
	private:
	object &object_;
	sge::string name_;
};
}
}

#endif
