#ifndef SGE_CONSOLE_HPP_INCLUDED
#define SGE_CONSOLE_HPP_INCLUDED

// C++
#include <vector>
#include <stdexcept>
#include <map>

// Boost
#include <boost/function.hpp>
#include <boost/lexical_cast.hpp>

#include "../string.hpp"
#include "../exception.hpp"
#include "../iconv.hpp"

namespace sge
{
namespace con
{
	typedef std::vector<string>                        arg_list;
	typedef boost::function<void (const arg_list &)>   function;

	class exception : public sge::exception
	{
	public:
		exception(const std::string &s) : sge::exception(s) {};
	};

	class var_base
	{
	public:
		var_base(const string&);
		const string &name() const;
		virtual void set_string(const string &) = 0;
		virtual string get_string() const = 0;
		virtual ~var_base();
	private:
		string name_;
	};

	template<typename T>
	struct var : public var_base
	{
		typedef T value_type;

		T value_;

		var(const string &name,const T &value_ = T()) : var_base(name),value_(value_) {}
		void value(const T &_value) { value_ = _value; }
		const T &value() const { return value_; }

		var<T> &operator=(const T &r) { value_ = r; return *this; }

		void set_string(const string &n) 
		{
			try {
				value_ = boost::lexical_cast<T>(n);
			} catch (const boost::bad_lexical_cast &e) {
				throw exception("Couldn't convert string \"" + iconv(n) + "\" to console variable!");
			}
		}

		string get_string() const { return boost::lexical_cast<string>(value_); }
	};

	template<typename T,typename A>
	struct action_var : public var_base
	{
		typedef T value_type;

		T value_;
		A action;
		
		action_var(const string &name,A _action,const T &_value = T()) : var_base(name),value_(_action(_value,_value)),action(_action) {}
		const T &value() const { return value_; }
		void value(const T &t) { t = action(t,value_); }
		action_var<T,A> &operator=(const T &r) { value_ = action(r,value_); return *this; }
		action_var<T,A> &operator=(const action_var<T,A> &r) { value_ = action(r.value_,value_); return *this; }

		void set_string(const string &n) 
		{
			try {
				value_ = action(boost::lexical_cast<T>(n),value_);
			} catch (const boost::bad_lexical_cast &e) {
				throw exception("Couldn't convert string \"" + iconv(n) + "\" to console variable!");
			}
		}

		string get_string() const { return boost::lexical_cast<string>(value_); }
	};

	class singleton
	{
	public:
		typedef std::map<string,var_base *> var_container;
		typedef std::map<string,function> func_container;
		typedef boost::function<void (const string &)> chat_callback_type;

		singleton();

		template<typename T>
		T get_value(const string &var_name)
		{
			if (vars_.find(var_name) == vars_.end())
				throw exception("A variable with name \"" + iconv(var_name) + "\" does not exist!");
			return boost::lexical_cast<T>(vars_[var_name]->get_string());
		}

		void set_value(const string &var_name,const string &t)
		{
			if (vars_.find(var_name) == vars_.end())
				throw exception("A variable with name \"" + iconv(var_name) + "\" does not exist!");
			vars_[var_name]->set_string(t);
		}

		var_container &vars();
		func_container &funcs();
		string::value_type prefix() const { return prefix_; }

		void add(const string &function_name,function fn);
		void add(const string &var_name,var_base &var);
		void remove(const string &var_name);
//		void read_config_file(const sge::string &);
		void prefix(const string::value_type n);
		void eval(const string &);
		void chat_callback(const chat_callback_type&);
	private:
		func_container funcs_;
		var_container  vars_;
		chat_callback_type chat_callback_;
		string::value_type prefix_;
	};

	singleton &instance();
}
}

#endif // CONSOLE_HPP
