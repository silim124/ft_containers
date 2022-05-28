/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: silim <silim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/28 15:44:09 by silim             #+#    #+#             */
/*   Updated: 2022/05/28 15:48:53 by silim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STACK_HPP
# define STACK_HPP
# include <deque>
# include <cstddef>

namespace ft
{
	template < class T, class Container = std::deque<T> >
	class stack
	{
		public:
			typedef T			value_type;
			typedef Container	container_type;
			typedef size_t		size_type;

		protected:
			container_type		c;

		// Constructor
		public:
			// default
			explicit stack(const container_type &con = container_type()) : c(con) {}

			// copy
			stack(const stack &other) : c(other.c) {}

			// Destructor
			~stack() {}

			// assignment operator
			stack	&operator=(const stack &other)
			{
				this->c = other.c;
				return (*this);
			}

		// Capacity
		public:
			// empty
			bool		empty() const
			{
				return (this->c.empty());
			}

			// size
			size_type	size() const
			{
				return (this->c.size());
			}

		public:
			// top
			value_type			&top()
			{
				return (this->c.back());
			}

			const value_type	&top() const
			{
				return (this->c.back());
			}

		// Modifiers
		public:
			// push
			void				push(const value_type &val)
			{
				this->c.push_back(val);
			}

			// pop
			void				pop()
			{
				this->c.pop_back();
			}

		// ==
		template <class T1, class Container1>
		friend bool operator==(const stack<T1, Container1>& lhs, const stack<T1, Container1>& rhs);

		// <
		template <class T1, class Container1>
		friend bool operator<(const stack<T1, Container1>& lhs, const stack<T1, Container1>& rhs);
	};

	// Relational operators
	template <class T, class Container>
	bool operator==(const stack<T,Container>& lhs, const stack<T,Container>& rhs)
	{
		return (lhs.c == rhs.c);
	}

	template <class T, class Container>
	bool operator!=(const stack<T,Container>& lhs, const stack<T,Container>& rhs)
	{
		return !(lhs == rhs);
	}

	template <class T, class Container>
	bool operator<(const stack<T,Container>& lhs, const stack<T,Container>& rhs)
	{
		return (lhs.c < rhs.c);
	}

	template <class T, class Container>
	bool operator<=(const stack<T,Container>& lhs, const stack<T,Container>& rhs)
	{
		return !(rhs < lhs);
	}

	template <class T, class Container>
	bool operator>(const stack<T,Container>& lhs, const stack<T,Container>& rhs)
	{
		return (rhs < lhs);
	}

	template <class T, class Container>
	bool operator>=(const stack<T,Container>& lhs, const stack<T,Container>& rhs)
	{
		return !(lhs < rhs);
	}
}

#endif
