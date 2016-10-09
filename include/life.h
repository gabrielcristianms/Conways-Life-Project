#ifndef __LIFE_H__
#define __LIFE_H__
#include <iostream>
#include <cassert>
#include <algorithms>
#include <cstdlib>

class Life{
	public:
		using size_type = unsigned long;

		Life( std::ostream );
		Life( const Life& )
		~Life();
		void update();
		void print() const;
		bool operator==() const;
		bool operator!=() const;
		Life& operator=( const Life& );
		friend std::ostream& operator<<( std::ostream, Life& );
	private:
		bool **m_cells;
		size_type m_height;
		size_type m_width;
};
#endif