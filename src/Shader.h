#ifndef __SHADER_H_
#define __SHADER_H_
#define __SHADER2C_H_
#define __SHADER2T_H_
#define __SHADER2P_H_

#include "Types.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Shader2c;
class Shader2t;
class Shader2p;

class Shader {
	public:
		static Shader2c * SHADER2C;
		static Shader2t * SHADER2T;
		static Shader2p * SHADER2P;
		static void init();
		GLint getUniformLoc(const char* name);
		void setProjection(glm::mat4);
		void setView(glm::mat4);
		void setModel(glm::mat4);
		void enable();
		void disable();
		~Shader();
	protected:
		Shader(const char vert[], const char frag[]);
		int32 program;
	private:
		uint32 projLoc, viewLoc, modelLoc;
		uint32 loadShader(const char path[], int32 type);
};

class Shader2c : public Shader {
	public:
		Shader2c();
		void setColor(float r, float g, float b, float a);
		~Shader2c();
	private:
		uint32 colorLoc;
		void getUniformLocs();
};

class Shader2t : public Shader {
	public:
		Shader2t();
		~Shader2t();
};

class Shader2p : public Shader {
public:
	Shader2p();
	void setDistance(float distance);
	~Shader2p();
private:
	float distanceLoc;
	void getUniformLocs();
};


#endif