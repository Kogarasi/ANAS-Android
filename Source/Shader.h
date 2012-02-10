
#ifndef __DEFINED_ANAS_SHADER__
#define __DEFINED_ANAS_SHADER__

#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>
#include <stdio.h>

#include "Uniform.h"

namespace ANAS {


	/**
	 * �V�F�[�_�[�p�̊��N���X<br>
	 * onInit/onSet�������z�֐�
	 * @author �R�K���V
	 */
	class ShaderBase {

		private:
			int shProgram;
			int shVertex;
			int shFragment;

			char *vString;
			char *fString;

			/**
			 * �V�F�[�_�[�f�[�^�̓ǂݍ��݁E�R���p�C��
			 * @param ShaderType �V�F�[�_�[�̎�ނ��w��
			 * @param Source �V�F�[�_�[�̃\�[�X�f�[�^
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
			 * �R���X�g���N�^
			 * @param vs ���_�V�F�[�_�[�p�̃\�[�X
			 * @param fs �t���O�����g�V�F�[�_�[�p�̃\�[�X
			 */
			ShaderBase( const char *vs, const char *fs ): shProgram(0), shVertex(0), shFragment(0){
				vString = new char [strlen(vs)];
				fString = new char [strlen(fs)];

				strcpy(vString, vs);
				strcpy(fString, fs);

			}
			/**
			 * �f�X�g���N�^
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
			 * �������֐�<br>
			 * �v�R���e�L�X�g�X���b�h���s
			 * �p�����onInit�֐����Ăяo�����
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
			 * �j���֐�<br>
			 * �v�R���e�L�X�g�X���b�h���s
			 */
			void Term(){
				
				glDetachShader( shProgram, shVertex );
				glDetachShader( shProgram, shFragment );
				glDeleteProgram( shProgram );
				glDeleteShader( shVertex );
				glDeleteShader( shFragment );

			}

			/**
			 * OpenGL�ւ̐ݒ�֐�<br>
			 * �v�R���e�L�X�g�X���b�h���s<br>
			 * �p�����onSet�֐����Ăяo�����
			 */
			void Set(){
				glUseProgram( shProgram );

				onSet();
			}

			/**
			 * �V�F�[�_�[�v���O������ID���擾
			 * @return �V�F�[�_�[�v���O����ID
			 */
			inline int GetProgram(){
				return shProgram;
			}


	};

};

#endif /* __DEFINED_ANAS_SHADER__ */