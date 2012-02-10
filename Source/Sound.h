
#ifndef __DEFINED_ANAS_SOUND__
#define __DEFINED_ANAS_SOUND__

#include <unistd.h>
#include <assert.h>

#include <SLES/OpenSLES.h>
#include <SLES/OpenSLES_Android.h>

#include "log.h"

namespace ANAS {

	/*
	class Sound {

		private:
			static SLObjectItf Engine;
			static SLEngineItf EngineInterface;

			static SLObjectItf OutMixer;

			SLObjectItf PlayerObject;
			SLPlayItf PlayerInterface;

		public:

			Sound(){

				ANAS::Log::i("Sound", "Construct");

				if(Engine == NULL){

					// エンジン生成
					slCreateEngine( &Engine, 0, NULL, 0, NULL, NULL );

					(*Engine)->Realize( Engine, SL_BOOLEAN_FALSE );
					(*Engine)->GetInterface( Engine, SL_IID_ENGINE, &EngineInterface );

					// ミキサー生成
					const SLInterfaceID ids[1] = { SL_IID_ENVIRONMENTALREVERB };
					const SLboolean req[1] = { SL_BOOLEAN_FALSE };
					(*EngineInterface)->CreateOutputMix( EngineInterface, &OutMixer, 1, ids, req );
					(*OutMixer)->Realize( OutMixer, SL_BOOLEAN_FALSE );
				} else {
					ANAS::Log::i("Sound", "Skip creating Engin");
				}

				ANAS::Log::i("Sound", "Construct");

			}

			void Load( int FileDescriptor, int file_ptr, int length ){
				SLresult result;

				ANAS::Log::i("Sound", "Load");


				// ソースデータの情報を設定
			    SLDataLocator_AndroidFD loc_fd = { SL_DATALOCATOR_ANDROIDFD, FileDescriptor, file_ptr, length };
				SLDataFormat_MIME format_mime = { SL_DATAFORMAT_MIME, NULL, SL_CONTAINERTYPE_UNSPECIFIED };
				SLDataSource audioSrc = {&loc_fd, &format_mime};

				// 出力先の設定
				SLDataLocator_OutputMix loc_outmix = {SL_DATALOCATOR_OUTPUTMIX, OutMixer};
				SLDataSink audioSnk = {&loc_outmix, NULL};

				
				const SLInterfaceID ids[3] = {SL_IID_SEEK, SL_IID_MUTESOLO, SL_IID_VOLUME};
				const SLboolean req[3] = {SL_BOOLEAN_TRUE, SL_BOOLEAN_TRUE, SL_BOOLEAN_TRUE};

				// プレイヤーの生成
				result = (*EngineInterface)->CreateAudioPlayer( EngineInterface, &PlayerObject, &audioSrc, &audioSnk, 3, ids, req);

				assert(SL_RESULT_SUCCESS == result);
				ANAS::Log::i("Sound", "CreateAudioPlayer");

				result = (*PlayerObject)->GetInterface( PlayerObject, SL_IID_PLAY, &PlayerInterface );
				assert(SL_RESULT_SUCCESS == result);
				ANAS::Log::i("Sound", "SL_IID_PLAY");
				
				SLSeekItf PlayerSeek;
				result = (*PlayerObject)->GetInterface(PlayerObject, SL_IID_SEEK, &PlayerSeek);
				assert(SL_RESULT_SUCCESS == result);
				ANAS::Log::i("Sound", "SL_IID_SEEK");
				//(*fdPlayerObject)->GetInterface(fdPlayerObject, SL_IID_MUTESOLO, &fdPlayerMuteSolo);
				//(*fdPlayerObject)->GetInterface(fdPlayerObject, SL_IID_VOLUME, &fdPlayerVolume);
				result = (*PlayerSeek)->SetLoop(PlayerSeek, SL_BOOLEAN_TRUE, 0, SL_TIME_UNKNOWN);
				assert(SL_RESULT_SUCCESS == result);
				ANAS::Log::i("Sound", "SetLoop");
				
				result = (*PlayerInterface)->SetPlayState(PlayerInterface, SL_PLAYSTATE_PLAYING );
				assert(SL_RESULT_SUCCESS == result);

				ANAS::Log::i("Sound", "SetPlayState");

			}

	};
	*/
}

#endif /* __DEFINED_ANAS_SOUND__ */