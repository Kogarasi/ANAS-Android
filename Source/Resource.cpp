#include <unistd.h>
#include <iostream>
#include <string>
#include <boost/unordered_map.hpp>
#include <boost/foreach.hpp>
#include "Resource.h"

namespace ANAS {

	typedef boost::unordered_map< std::string, ResourceHolder* > ResourceMap;

	class ResourceImpl {

		public:
			ResourceMap MapData;

			ResourceImpl(){}
			~ResourceImpl(){

				BOOST_FOREACH( ResourceMap::value_type value, MapData ){
					delete value.second;
				}
			}

	};
}

ANAS::Resource::Resource(){

	pImpl = new ResourceImpl;
}

ANAS::Resource::~Resource(){

	if(pImpl){
		delete pImpl;
	}
}

// ���\�[�X��ǉ�
void ANAS::Resource::Set( const std::string &Name, ResourceHolder* pHold ){

	pImpl->MapData[ Name ] = pHold;
}

// ���\�[�X���擾
ANAS::ResourceHolder *ANAS::Resource::Get( const std::string &Name ){

	// �m�F
	if( pImpl->MapData.count( Name ) ){
		
		return pImpl->MapData.at( Name );

	} else {
		return NULL;
	}
}

// ���\�[�X�̊J��
void ANAS::Resource::Release( const std::string &Name ){

	if( pImpl->MapData.count( Name ) ){

		pImpl->MapData.erase( Name );
	}
}