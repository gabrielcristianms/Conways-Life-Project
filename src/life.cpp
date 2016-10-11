#include "life.h"

Life::Life( size_type _h = 0, size_type _w = 0)
	: m_height { _h }
	, m_width { _w }
{
	m_cells = new int* [m_height+2];
	for(size_type i = 0; i < m_height+2; ++i)
		m_cells[i] = new int [m_width+2];

	for(size_type i = 0; i < m_height+2; ++i) {
		for( size_type j = 0; j < m_width+2; ++j) {
			m_cells[i][j] = 0;
		}
	}
}

Life::~Life(){
	for(size_type i = 0; i < m_width+2; ++i)
		delete [] m_cells[i];
	delete [] m_cells;
}

void
Life::setAlive( std::stringstream &_file ){
	std::vector<std::string> line;
	std::string temp;
	_file >> temp;
	std::cout << temp << "\n";

	// A ideia é utilizar a stringstream e um for para ler a linhas e inicializar a matriz, não esqueça

	/*std::istringstream colony( _file );
	for( std::string cell; std::getline( colony, cell ); line.push_back( cell ) ){
		std::cout << "Oi\n";
	} */
}

bool
Life::operator==( Life &_rhs ){
	if( this->m_height != _rhs.m_height ) return false;
	if( this->m_width != _rhs.m_width ) return false;

	for(size_type i = 1; i <= this->m_height; ++i) {
		for( size_type j = 1; j <= this->m_width; ++j) {
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
	// Deletes the memory allocated previously
	for(size_type i = 0; i < this->m_width+2; ++i)
		delete [] this->m_cells[i];
	delete [] this->m_cells;

	// Allocates the new space we'll use
	this->m_cells = new int* [m_height+2];
	for(size_type i = 0; i < m_height+2; ++i)
		m_cells[i] = new int [m_width+2];

	// Copying the measures of our cells matrix
	this->m_height = _rhs.m_height;
	this->m_width  = _rhs.m_width;

	// Copying the values of _rhs.m_cells to the object this->m_cells who called =() 
	for(size_type i = 0; i < this->m_height+2; ++i) {
		for( size_type j = 0; j < this->m_width+2; ++j) {
			this->m_cells[i][j] = _rhs.m_cells[i][j];
		}
	}	
	return *this;
}