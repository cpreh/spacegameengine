#ifndef SGE_CONSOLE_VAR_BASE_HPP_INCLUDED
#define SGE_CONSOLE_VAR_BASE_HPP_INCLUDED

#include <sge/console/object_fwd.hpp>
#include <sge/string.hpp>
#include <boost/noncopyable.hpp>

namespace sge
{
namespace console
{
class var_base : public boost::noncopyable
{
	public:
	var_base(
		object &,
		sge::string const &);
	
	virtual void string(sge::string const &) = 0;
	virtual sge::string const string() const = 0;

	sge::string const name() const;
	
	virtual ~var_base();
	private:
	object &object_;
	sge::string name_;
};
}
}

#endif
