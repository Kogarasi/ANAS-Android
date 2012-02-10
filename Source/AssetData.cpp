
#include "AssetData.h"

// �R���X�g���N�^
ANAS::AssetData::AssetData( AAssetManager *_manager )
	: DataLength(0), ByteData(NULL), pAssetManager( _manager ), OpenMode(AASSET_MODE_STREAMING)
{
}

// �f�X�g���N�^
ANAS::AssetData::~AssetData(){
	if(ByteData){
		delete[] ByteData;
	}
}

// �A�Z�b�g�f�[�^�̓ǂݍ���
void ANAS::AssetData::Load( const char * asset_name ){

	// �O�ɓǂݍ��񂾃f�[�^��j��
	Destroy();

	// �A�Z�b�g���擾
	AAsset *_asset = AAssetManager_open( pAssetManager, asset_name, OpenMode);
				
	// �A�Z�b�g�����擾
	DataLength = AAsset_getLength( _asset );
	const void *Asset_ptr = AAsset_getBuffer( _asset );

	// �f�[�^�R�s�[
	ByteData = new char[ DataLength+1 ];
	for(int i=0; i<DataLength+1; i++){ ByteData[ i] = 0; }
	memcpy( ByteData, Asset_ptr, DataLength );
				

	// �I���
	AAsset_close( _asset );
}

void ANAS::AssetData::Load_CB( const char * asset_name, void(*func)(const char*, int) ){

	// �A�Z�b�g���擾
	AAsset *_asset = AAssetManager_open( pAssetManager, asset_name, OpenMode);
				
	// �A�Z�b�g�����擾
	DataLength = AAsset_getLength( _asset );
	const void *Asset_ptr = AAsset_getBuffer( _asset );

	// �R�[���o�b�N�Ɉڏ�
	func( (const char*)Asset_ptr, DataLength );

				
	// �I���
	AAsset_close( _asset );
}