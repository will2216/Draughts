#pragma once

namespace blib
{
	struct pos
	{
		int m_x;
		int m_y;


		int& operator[](const int &index) 
		{
			if (index == 1)
				return m_y;
			else 
				return m_x;
		} 

		int operator[](const int &index) const
		{
			if (index == 1)
				return m_y;
			else
				return m_x;
		}

		pos& operator++()
		{
			m_x++;
			m_y++;
			return *this;
		}
		pos& operator--()
		{
			m_x--;
			m_y--;
			return *this;
		}
		pos operator++(int)  
		{
			pos result(*this);   
			++(*this);              
			return result;          
		}
		pos operator--(int)
		{
			pos result(*this);
			--(*this);
			return result;
		}

		// shift position to the "down" (num) times.
		void operator+=(const int &num)
		{
			m_x += num;
		}

		// shift position to the "up" (num) times.
		void operator-=(const int &num)
		{
			m_x -= num;
		}

		// shift position to the "left" (num) times.
		void operator<<=(const int &num)
		{
			m_y -= num;
		}

		// shift position to the "right" (num) times.
		void operator>>=(const int &num)
		{
			m_y += num;
		}

		pos operator+(const int &num)
		{
			return pos{ m_x + num, m_y };
		}

		pos operator-(const int &num)
		{
			return pos{ m_x - num, m_y };
		}

		pos operator<<(const int &num)
		{
			return pos{ m_x, m_y - num };
		}

		pos operator>>(const int &num)
		{
			return pos{ m_x, m_y + num };
		}

		// Multiplication operator
		pos operator*(const int &num)
		{
			return { m_x*num, m_y*num };
		}

		// comparison operator
		bool operator==(const int (&array)[2])
		{
			return (array[0] == m_x && array[1] == m_y);
		}

		bool operator==(const pos &input)
		{
			return (input.m_x == m_x && input.m_y == m_y);
		}


		pos()
			: m_x(0), m_y(0)
		{

		}

		pos(const int &x, const int &y)
			: m_x(x), m_y(y)
		{

		}

		pos(const int (&position)[2] )
			: m_x(position[0]), m_y(position[1])
		{

		}
	};
	
}