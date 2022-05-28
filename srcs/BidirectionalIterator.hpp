/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BidirectionalIterator.hpp                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: silim <silim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/28 15:43:41 by silim             #+#    #+#             */
/*   Updated: 2022/05/28 15:49:13 by silim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BIDIRECTIONALITERATOR_HPP
# define BIDIRECTIONALITERATOR_HPP
# include "Iterator.hpp"
# include "IteratorTraits.hpp"
# include <cstddef>

namespace ft
{
	template < class T, class Pointer, class Reference,
			 class Category = ft::bidirectional_iterator_tag >
	class BidirectionalIterator : public Iterator< Category, T >
	{
		public:
			typedef Iterator<Category, T>							base_iterator;
			typedef BidirectionalIterator<T, T*, T&>				iterator;
			typedef BidirectionalIterator<T, const T*, const T&>	const_iterator;
			typedef ptrdiff_t										difference_type;
			typedef T*												pointer;
			typedef T&												reference;
			typedef Category										iterator_category;

		public:
			BidirectionalIterator() : base_iterator() {}

			BidirectionalIterator(pointer ptr) : base_iterator(ptr) {}

			~BidirectionalIterator() {}

			BidirectionalIterator(BidirectionalIterator const &src)
			{
				*this = src;
			}

			iterator	&operator=(iterator const &src)
			{
				this->_ptr = src._ptr;
				return (*this);
			}

			bool		operator==(iterator const &src)
			{
				return (this->_ptr == src._ptr);
			}

			bool		operator!=(iterator const &src)
			{
				return !(*this == src);
			}

			reference	operator*() const
			{
				return (*this->_ptr);
			}

			pointer		operator->() const
			{
				return (&(*this->_ptr));
			}

			iterator	&operator++()
			{
				this->_ptr++;
				return (*this);
			}

			iterator	operator++(int)
			{
				iterator	it = *this;

				this->_ptr++;
				return (it);
			}

			iterator	&operator--()
			{
				this->_ptr--;
				return (*this);
			}

			iterator	operator--(int)
			{
				iterator	it = *this;

				this->_ptr--;
				return (it);
			}

			template <class T1, class T2, class T3>
			friend bool operator==(BidirectionalIterator< T1, T2*, T2& > const &lhs, BidirectionalIterator< T1, T3*, T3& > const &rhs);
	};

	template <class T1, class T2, class T3>
	bool operator==(BidirectionalIterator< T1, T2*, T2& > const &lhs,
			BidirectionalIterator< T1, T3*, T3& > const &rhs)
	{
		return (lhs._ptr == rhs._ptr);
	}

	template <class T1, class T2, class T3>
	bool operator!=(BidirectionalIterator< T1, T2*, T2& > const &lhs,
			BidirectionalIterator< T1, T3*, T3& > const &rhs)
	{
		return !(lhs == rhs);
	}
}

#endif
