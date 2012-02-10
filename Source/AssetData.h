
#ifndef __DEFINED_ANAS_ASSETDATA__
#define __DEFINED_ANAS_ASSETDATA__

#include <unistd.h>
#include <android/asset_manager.h>

namespace ANAS {

	/**
	 * �A�Z�b�g�f�[�^��ǂݍ��ނ��߂̃N���X
	 * @author �R�K���V
	 */
	class AssetData {

		private:
			AAssetManager	*pAssetManager;
			int OpenMode;

			unsigned int	DataLength;
			char			*ByteData;	// Byte Array

			// �����Ȃ�
			AssetData();
		public:

			AssetData(AAssetManager *);
			~AssetData();

			/**
			 * �A�Z�b�g�f�[�^�̓ǂݍ���
			 * @param asset_name �A�Z�b�g�f�[�^�̃t�@�C����
			 */
			void Load( const char * asset_name );

			/**
			 * �A�Z�b�g�f�[�^�̓ǂݍ��݁i�R�[���o�b�N�Łj<br>
			 * �A�Z�b�g�f�[�^���R�s�[�����ɒ��ڈ����̂Ń����������}������
			 * @param asset_name �A�Z�b�g�f�[�^�̃t�@�C����
			 * @param func ����������R�[���o�b�N�֐�
			 */
			void Load_CB( const char * asset_name, void(*func)(const char*, int) );

			/**
			 * �A�Z�b�g�f�[�^�̓ǂݍ��݁i�R�[���o�b�N�Łj<br>
			 * �A�Z�b�g�f�[�^���R�s�[�����ɒ��ڈ����̂Ń����������}������<br>
			 * �A�Z�b�g�f�[�^�T�C�Y��K�v�Ƃ��Ȃ��ꍇ
			 * @param asset_name �A�Z�b�g�f�[�^�̃t�@�C����
			 * @param func ����������R�[���o�b�N�֐�
			 */
			void Load_CB( const char * asset_name, void(*func)(const char*) ){

				// �A�Z�b�g���擾
				AAsset *_asset = AAssetManager_open( pAssetManager, asset_name, OpenMode);
				
				// �A�Z�b�g�����擾
				const void *Asset_ptr = AAsset_getBuffer( _asset );

				// �R�[���o�b�N�Ɉڏ�
				func( (const char*)Asset_ptr );

				
				// �I���
				AAsset_close( _asset );
			}

			/**
			 * �ǂݍ��񂾃A�Z�b�g�f�[�^�̔j��
			 */
			void Destroy(){
				if(DataLength){
					DataLength = 0;
					delete[] ByteData;
					ByteData = NULL;
				}
			}
			/**
			 * �ǂݍ��񂾃A�Z�b�g�f�[�^�̎擾
			 * @return �A�Z�b�g�f�[�^��
			 */
			const char *GetData(){
				return ByteData;
			}

			/**
			 * �t�@�C���f�B�X�N���v�^���擾
			 * @param asset_name �擾����A�Z�b�g��
			 * @param fd �t�@�C���f�B�X�N���v�^
			 * @param file_ptr �t�@�C���ʒu
			 * @param length �t�@�C���T�C�Y
			 */
			void GetFileDescriptor(const char *asset_name, int *fd, int *file_ptr, int *length ){
				
				// �A�Z�b�g���擾
				AAsset *_asset = AAssetManager_open( pAssetManager, asset_name, AASSET_MODE_BUFFER);
				
				off_t ptr, len;
				
				*fd = AAsset_openFileDescriptor( _asset, &ptr, &len );

				*file_ptr = ptr;
				*length = len;

				
				// �I���
				AAsset_close( _asset );

			}

	};
}

#endif /* __DEFINED_ANAS_ASSETDATA__ */