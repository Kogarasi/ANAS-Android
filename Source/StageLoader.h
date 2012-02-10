
#ifndef __DEFINED_GAME_STAGE_LOADER__
#define __DEFINED_GAME_STAGE_LOADER__

#include <iostream>
#include <string>

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>

namespace Game {

	class StageLoader {
		private:
		public:

			// �R���X�g���N�^
			StageLoader(){
			}

			// �f�X�g���N�^
			~StageLoader(){}

			// �ǂݍ��݊֐�
			void LoadXML( const char *xml_data ){

				std::istringstream _istream( xml_data );

				boost::property_tree::ptree _ptree;
				boost::property_tree::read_xml( _istream, _ptree );
				
			}

	};
}

#endif /* __DEFINED_GAME_STAGE_LOADER__ */