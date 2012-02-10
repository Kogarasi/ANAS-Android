
#ifndef __DEFINED_ANAS_SHADER__
#define __DEFINED_ANAS_SHADER__

#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>
#include <stdio.h>

#include "Uniform.h"

namespace ANAS {


	/**
	 * シェーダー用の基底クラス<br>
	 * onInit/onSetが純仮想関数
	 * @author コガラシ
	 */
	class ShaderBase {

		private:
			int shProgram;
			int shVertex;
			int shFragment;

			char *vString;
			char *fString;

			/**
			 * シェーダーデータの読み込み・コンパイル
			 * @param ShaderType シェーダーの種類を指定
			 * @param Source シェーダーのソースデータ
			 */
			int LoadShader( int ShaderType, const char *Source ){

				int newShader = glCreateShader( ShaderType );
				if( newShader ){

					glShaderSource( newShader, 1, &Source, NULL );
					glCompileShader( newShader );

					
					GLint compiled = 0;
					glGetShaderiv(newShader, GL_COMPILE_STATUS, &compiled);
					if( compiled == 0 ){
						ANAS::Log::i("Shader", "Compile Failed");
						ANAS::Log::i("Shader", Source);
					}

				}
				
				return newShader;

			}
		protected:
			
			virtual void onInit() = 0;
			virtual void onSet() = 0;

		public:

			/**
			 * コンストラクタ
			 * @param vs 頂点シェーダー用のソース
			 * @param fs フラグメントシェーダー用のソース
			 */
			ShaderBase( const char *vs, const char *fs ): shProgram(0), shVertex(0), shFragment(0){
				vString = new char [strlen(vs)];
				fString = new char [strlen(fs)];

				strcpy(vString, vs);
				strcpy(fString, fs);

			}
			/**
			 * デストラクタ
			 */
			virtual ~ShaderBase(){

				if(vString){ delete[] vString; }
				if(fString){ delete[] fString; }

				glUseProgram( NULL );

				glDetachShader( shProgram, shVertex );
				glDetachShader( shProgram, shFragment );

				glDeleteShader( shVertex );
				glDeleteShader( shFragment );

				glDeleteProgram( shProgram );

			}

			/**
			 * 初期化関数<br>
			 * 要コンテキストスレッド実行
			 * 継承先のonInit関数が呼び出される
			 */
			void Init(){

				// Load Shader
				shVertex = LoadShader( GL_VERTEX_SHADER, vString );
				shFragment = LoadShader( GL_FRAGMENT_SHADER, fString );


				// Create Program
				shProgram = glCreateProgram();

				if( shProgram ){
					// Link Program
					glAttachShader( shProgram, shVertex );
					glAttachShader( shProgram, shFragment );

					glLinkProgram( shProgram );
					
					GLint linkStatus = GL_FALSE;
					glGetProgramiv(shProgram, GL_LINK_STATUS, &linkStatus);
					
					if( linkStatus != GL_TRUE ){
						ANAS::Log::i("Shader", "Link Failed");
					}



				} else {
					ANAS::Log::i("Shader","Can't create program");
				}

				delete[] vString;
				vString = NULL;
				delete[] fString;
				fString = NULL;


				onInit();

			}

			/**
			 * 破棄関数<br>
			 * 要コンテキストスレッド実行
			 */
			void Term(){
				
				glDetachShader( shProgram, shVertex );
				glDetachShader( shProgram, shFragment );
				glDeleteProgram( shProgram );
				glDeleteShader( shVertex );
				glDeleteShader( shFragment );

			}

			/**
			 * OpenGLへの設定関数<br>
			 * 要コンテキストスレッド実行<br>
			 * 継承先のonSet関数が呼び出される
			 */
			void Set(){
				glUseProgram( shProgram );

				onSet();
			}

			/**
			 * シェーダープログラムのIDを取得
			 * @return シェーダープログラムID
			 */
			inline int GetProgram(){
				return shProgram;
			}


	};

};

#endif /* __DEFINED_ANAS_SHADER__ */