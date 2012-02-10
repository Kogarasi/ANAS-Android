
#ifndef __DEFINED_ANAS_UNIFORM__
#define __DEFINED_ANAS_UNIFORM__

#include "boost/format.hpp"

#include <GLES2/gl2.h>

namespace ANAS {

	/**
	 * �V�F�[�_�[��Uniform���������߂̊��N���X
	 * @author �R�K���V
	 */
	class UniformBase {
		protected:

			const char* UniformName;
			int			UniformLocation;
			int			ProgramNum;

			inline void GetLocation(){
				
				UniformLocation = glGetUniformLocation( ProgramNum, UniformName );

				ANAS::Log::i( "Uniform", (boost::format("Name:%1%, No:%2%")%UniformName%UniformLocation).str().c_str() );
			}


		public:

			UniformBase(): UniformLocation(-1){}

			/**
			 * ������
			 * @param program �V�F�[�_�[�v���O����ID
			 * @param name Uniform�̖��O
			 */
			void Init( int program, const char *name){
				ProgramNum = program;
				UniformName = name;

				GetLocation();
			}

	};

	/**
	 * �V�F�[�_�[��Uniform���������߂̃N���X<br>
	 * �e���v���[�g�Ō^�Ɨv�f�����w��
	 * @author �R�K���V
	 */
	template <typename T, int N> class Uniform : public UniformBase {
		
		public:
			Uniform(){}
	};

	// int,1
	template<> class Uniform<int,1> : public UniformBase{
		public:


			/**
			 * Uniform�ɒl�𔽉f
			 * @param arg Uniform�ɐݒ肷��l
			 */
			void SetValue(int arg){

				glUniform1i( UniformLocation, arg);
			}
	};

	// int,2
	template<> class Uniform<int,2> : public UniformBase{
		public:

			/**
			 * Uniform�ɒl�𔽉f
			 * @param arg Uniform�ɐݒ肷��l
			 */
			void SetValue(int arg0, int arg1){

				glUniform2i( UniformLocation, arg0, arg1);
			}
	};
	
	// int,3
	template<> class Uniform<int,3> : public UniformBase{
		public:

			/**
			 * Uniform�ɒl�𔽉f
			 * @param arg Uniform�ɐݒ肷��l
			 */
			void SetValue(int arg0, int arg1, int arg2){

				glUniform3i( UniformLocation, arg0, arg1, arg2);
			}
	};
	
	// int,4
	template<> class Uniform<int,4> : public UniformBase{
		public:

			/**
			 * Uniform�ɒl�𔽉f
			 * @param arg Uniform�ɐݒ肷��l
			 */
			void SetValue(int arg0, int arg1, int arg2, int arg3){

				glUniform4i( UniformLocation, arg0, arg1, arg2, arg3);
			}
	};
	
	// float,1
	template<> class Uniform<float,1> : public UniformBase{
		public:

			/**
			 * Uniform�ɒl�𔽉f
			 * @param arg Uniform�ɐݒ肷��l
			 */
			void SetValue(float arg){

				glUniform1f( UniformLocation, arg);
			}
	};
	
	// float,2
	template<> class Uniform<float,2> : public UniformBase{
		public:

			/**
			 * Uniform�ɒl�𔽉f
			 * @param arg Uniform�ɐݒ肷��l
			 */
			void SetValue(float arg0, float arg1){

				glUniform2f( UniformLocation, arg0, arg1);
			}
	};
	
	// float,3
	template<> class Uniform<float,3> : public UniformBase{
		public:

			/**
			 * Uniform�ɒl�𔽉f
			 * @param arg Uniform�ɐݒ肷��l
			 */
			void SetValue(float arg0, float arg1, float arg2){

				glUniform3f( UniformLocation, arg0, arg1, arg2);
			}
	};
	
	// float,4
	template<> class Uniform<float,4> : public UniformBase{
		public:

			/**
			 * Uniform�ɒl�𔽉f
			 * @param arg Uniform�ɐݒ肷��l
			 */
			void SetValue(float arg0, float arg1, float arg2, float arg3){

				glUniform4f( UniformLocation, arg0, arg1, arg2, arg3);
			}
	};

}


#endif /* __DEFINED_ANAS_UNIFORM__ */