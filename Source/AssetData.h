
#ifndef __DEFINED_ANAS_ASSETDATA__
#define __DEFINED_ANAS_ASSETDATA__

#include <unistd.h>
#include <android/asset_manager.h>

namespace ANAS {

	/**
	 * アセットデータを読み込むためのクラス
	 * @author コガラシ
	 */
	class AssetData {

		private:
			AAssetManager	*pAssetManager;
			int OpenMode;

			unsigned int	DataLength;
			char			*ByteData;	// Byte Array

			// 引数なし
			AssetData();
		public:

			AssetData(AAssetManager *);
			~AssetData();

			/**
			 * アセットデータの読み込み
			 * @param asset_name アセットデータのファイル名
			 */
			void Load( const char * asset_name );

			/**
			 * アセットデータの読み込み（コールバック版）<br>
			 * アセットデータをコピーせずに直接扱うのでメモリ消費を抑えられる
			 * @param asset_name アセットデータのファイル名
			 * @param func 処理をするコールバック関数
			 */
			void Load_CB( const char * asset_name, void(*func)(const char*, int) );

			/**
			 * アセットデータの読み込み（コールバック版）<br>
			 * アセットデータをコピーせずに直接扱うのでメモリ消費を抑えられる<br>
			 * アセットデータサイズを必要としない場合
			 * @param asset_name アセットデータのファイル名
			 * @param func 処理をするコールバック関数
			 */
			void Load_CB( const char * asset_name, void(*func)(const char*) ){

				// アセットを取得
				AAsset *_asset = AAssetManager_open( pAssetManager, asset_name, OpenMode);
				
				// アセット情報を取得
				const void *Asset_ptr = AAsset_getBuffer( _asset );

				// コールバックに移譲
				func( (const char*)Asset_ptr );

				
				// 終わり
				AAsset_close( _asset );
			}

			/**
			 * 読み込んだアセットデータの破棄
			 */
			void Destroy(){
				if(DataLength){
					DataLength = 0;
					delete[] ByteData;
					ByteData = NULL;
				}
			}
			/**
			 * 読み込んだアセットデータの取得
			 * @return アセットデータ列
			 */
			const char *GetData(){
				return ByteData;
			}

			/**
			 * ファイルディスクリプタを取得
			 * @param asset_name 取得するアセット名
			 * @param fd ファイルディスクリプタ
			 * @param file_ptr ファイル位置
			 * @param length ファイルサイズ
			 */
			void GetFileDescriptor(const char *asset_name, int *fd, int *file_ptr, int *length ){
				
				// アセットを取得
				AAsset *_asset = AAssetManager_open( pAssetManager, asset_name, AASSET_MODE_BUFFER);
				
				off_t ptr, len;
				
				*fd = AAsset_openFileDescriptor( _asset, &ptr, &len );

				*file_ptr = ptr;
				*length = len;

				
				// 終わり
				AAsset_close( _asset );

			}

	};
}

#endif /* __DEFINED_ANAS_ASSETDATA__ */