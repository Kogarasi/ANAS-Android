
#include "AssetData.h"

// コンストラクタ
ANAS::AssetData::AssetData( AAssetManager *_manager )
	: DataLength(0), ByteData(NULL), pAssetManager( _manager ), OpenMode(AASSET_MODE_STREAMING)
{
}

// デストラクタ
ANAS::AssetData::~AssetData(){
	if(ByteData){
		delete[] ByteData;
	}
}

// アセットデータの読み込み
void ANAS::AssetData::Load( const char * asset_name ){

	// 前に読み込んだデータを破棄
	Destroy();

	// アセットを取得
	AAsset *_asset = AAssetManager_open( pAssetManager, asset_name, OpenMode);
				
	// アセット情報を取得
	DataLength = AAsset_getLength( _asset );
	const void *Asset_ptr = AAsset_getBuffer( _asset );

	// データコピー
	ByteData = new char[ DataLength+1 ];
	for(int i=0; i<DataLength+1; i++){ ByteData[ i] = 0; }
	memcpy( ByteData, Asset_ptr, DataLength );
				

	// 終わり
	AAsset_close( _asset );
}

void ANAS::AssetData::Load_CB( const char * asset_name, void(*func)(const char*, int) ){

	// アセットを取得
	AAsset *_asset = AAssetManager_open( pAssetManager, asset_name, OpenMode);
				
	// アセット情報を取得
	DataLength = AAsset_getLength( _asset );
	const void *Asset_ptr = AAsset_getBuffer( _asset );

	// コールバックに移譲
	func( (const char*)Asset_ptr, DataLength );

				
	// 終わり
	AAsset_close( _asset );
}