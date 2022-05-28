/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RandomAccessIterator.hpp                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: silim <silim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/28 15:44:03 by silim             #+#    #+#             */
/*   Updated: 2022/05/28 15:48:58 by silim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RANDOMACCESSITERATOR_HPP
# define RANDOMACCESSITERATOR_HPP
# include "BidirectionalIterator.hpp"
# include "IteratorTraits.hpp"
# include <cstddef>

namespace ft
{
	template < class T, class Pointer = T*, class Reference = T&,
			 class Category = ft::random_access_iterator_tag >
	class RandomAccessIterator : public BidirectionalIterator< T, T*, T&, Category >
	{
		public:
			typedef RandomAccessIterator<T, T*, T&>				iterator;
			typedef RandomAccessIterator<T, const T*, const T&>	const_iterator;
			typedef	BidirectionalIterator<T, T*, T&, Category>	bidirectional_iterator;
			typedef ptrdiff_t									difference_type;
			typedef T*											pointer;
			typedef T&											reference;
			typedef Category									iterator_category;

		public:
			RandomAccessIterator() : bidirectional_iterator() {}

			RandomAccessIterator(pointer ptr) : bidirectional_iterator(ptr) {}

			~RandomAccessIterator() {}

			RandomAccessIterator(RandomAccessIterator const &src)
			{
				*this = src;
			}

			RandomAccessIterator	&operator=(RandomAccessIterator const &src)
			{
				this->_ptr = src._ptr;
				return (*this);
			}

			RandomAccessIterator	operator+(difference_type const &n) const
			{
				iterator	it = *this;

				it._ptr += n;
				return (it);
			}


			RandomAccessIterator	operator-(difference_type const &n) const
			{
				iterator	it = *this;

				it._ptr -= n;
				return (it);
			}

			difference_type			operator-(RandomAccessIterator const &val) const
			{
				return (this->_ptr - val._ptr);
			}

			iterator				operator+=(difference_type const &n)
			{
				this->_ptr += n;
				return (*this);
			}

			iterator				operator-=(difference_type const &n)
			{
				this->_ptr -= n;
				return (*this);
			}

			reference				operator[](difference_type const &n) const
			{
				return (*(this->_ptr + n));
			}

			RandomAccessIterator	&operator++()
			{
				this->_ptr++;
				return (*this);
			}

			RandomAccessIterator	operator++(int)
			{
				iterator	it = *this;

				this->_ptr++;
				return (it);
			}

			RandomAccessIterator	&operator--()
			{
				this->_ptr--;
				return (*this);
			}

			RandomAccessIterator	operator--(int)
			{
				iterator	it = *this;

				this->_ptr--;
				return (it);
			}

			operator				iterator() const
			{
				return (iterator(this->_ptr));
			}

			operator				const_iterator() const
			{
				return (const_iterator(this->_ptr));
			}

			template <class T1, class T2, class T3>
			friend bool	operator==(RandomAccessIterator< T1, T2*, T2& > const &lhs, RandomAccessIterator< T1, T3*, T3& > const &rhs);

			template <class T1, class T2, class T3>
			friend bool	operator<(RandomAccessIterator< T1, T2*, T2& > const &lhs, RandomAccessIterator< T1, T3*, T3& > const &rhs);
		};

	template <class T>
	RandomAccessIterator<T, T*, T&>	operator+(typename RandomAccessIterator< T, T*, T& >::difference_type const &n, RandomAccessIterator< T, T*, T& > const &iterator)
	{
		return (iterator + n);
	}

	template <class T1, class T2, class T3>
	bool	operator==(RandomAccessIterator< T1, T2*, T2& > const &lhs, RandomAccessIterator< T1, T3*, T3& > const &rhs)
	{
		return (lhs._ptr == rhs._ptr);
	}

	template <class T1, class T2, class T3>
	bool	operator!=(RandomAccessIterator< T1, T2*, T2& > const &lhs, RandomAccessIterator< T1, T3*, T3& > const &rhs)
	{
		return !(lhs == rhs);
	}

	template <class T1, class T2, class T3>
	bool	operator<(RandomAccessIterator< T1, T2*, T2& > const &lhs, RandomAccessIterator< T1, T3*, T3& > const &rhs)
	{
		return (lhs._ptr < rhs._ptr);
	}

	template <class T1, class T2, class T3>
	bool	operator>(RandomAccessIterator< T1, T2*, T2& > const &lhs, RandomAccessIterator< T1, T3*, T3& > const &rhs)
	{
		return (rhs < lhs);
	}

	template <class T1, class T2, class T3>
	bool	operator<=(RandomAccessIterator< T1, T2*, T2& > const &lhs, RandomAccessIterator< T1, T3*, T3& > const &rhs)
	{
		return (!(rhs < lhs));
	}

	template <class T1, class T2, class T3>
	bool	operator>=(RandomAccessIterator< T1, T2*, T2& > const &lhs, RandomAccessIterator< T1, T3*, T3& > const &rhs)
	{
		return (!(lhs < rhs));
	}
}

#endif
