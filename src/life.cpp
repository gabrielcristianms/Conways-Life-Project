#include "life.h"

Life::Life( size_type _h = 0, size_type _w = 0)
	: m_height { _h }
	, m_width { _w }
{
	m_cells = new int* [m_height];
	for(size_type i = 0; i < m_height; ++i)
		m_cells[i] = new int [m_width];

	for(size_type i = 0; i < m_height; ++i) {
		for( size_type j = 0; j < m_width; ++j) {
			m_cells[i][j] = 0;
		}
	}
}

Life::~Life(){
	for(size_type i = 0; i < m_width; ++i)
		delete [] m_cells[i];
	delete [] m_cells;
}

/*void
Life::setAlive( const std::stringstream &_file ){
	for(size_type i = 0; i < m_height; ++i) {
		std::string line = _file.getline();
		for( size_type j = 0; j < m_width; ++j) {
			m_cells[i][j] = line[j];
		}
	}
}*/

bool
Life::operator==( Life &_rhs ){
	if( this->m_height != _rhs.m_height ) return false;
	if( this->m_width != _rhs.m_width ) return false;

	for(size_type i = 0; i < this->m_height; ++i) {
		for( size_type j = 0; j < this->m_width; ++j) {
			if( this->m_cells[i][j] != _rhs.m_cells[i][j]) return false;
		}
	}
	return true;
}

bool
Life::operator!=( Life &_rhs ){
	return !( *this == _rhs );
}

Life&
Life::operator=( const Life &_rhs ){
	delete [] this->m_cells;

	this->m_cells = new int* [m_height];
	for(size_type i = 0; i < m_height; ++i)
		m_cells[i] = new int [m_width];

	this->m_height = _rhs.m_height;
	this->m_width  = _rhs.m_width;

	for(size_type i = 0; i < this->m_height; ++i) {
		for( size_type j = 0; j < this->m_width; ++j) {
			this->m_cells[i][j] = _rhs.m_cells[i][j];
		}
	}	
	
	return *this;
}