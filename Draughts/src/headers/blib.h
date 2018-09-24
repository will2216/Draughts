#pragma once

namespace blib
{
	struct pos
	{
		int m_x;
		int m_y;


		int& operator[](const int &index) 
		{
			return index ? m_y : m_x;
		}

		void operator++()
		{
			m_x++;
			m_y++;
		}

		void operator--()
		{
			m_x--;
			m_y--;
		}


		pos()
			: m_x(0), m_y(0)
		{

		}

		pos(int x, int y)
			: m_x(x), m_y(y)
		{

		}

		pos(int (&position)[2] )
			: m_x(position[0]), m_y(position[1])
		{

		}
	};
	
}