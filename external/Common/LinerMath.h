#pragma once

#undef NOMINMAX
#include <algorithm>
#include <iomanip>

struct vec3f
{
    vec3f() : x(0.f), y(0.f), z(0.f) {};
    vec3f(float f) : x(f), y(f), z(f) {};
    vec3f(float x, float y, float z) : x(x), y(y), z(z) {};
    float x,y,z;
};


struct mat4f
{
    mat4f(){
        memset(f, 0, sizeof(f));
        m[0][0] = m[1][1] = m[2][2] = m[3][3] = 1.0f;
    }

    mat4f(
    float m00, float m01, float m02, float m03,
	float m10, float m11, float m12, float m13,
	float m20, float m21, float m22, float m23,
	float m30, float m31, float m32, float m33)
    {
	    m[0][0] = m00; m[0][1] = m01; m[0][2] = m02; m[0][3] = m03;
	    m[1][0] = m10; m[1][1] = m11; m[1][2] = m12; m[1][3] = m13;
	    m[2][0] = m20; m[2][1] = m21; m[2][2] = m22; m[2][3] = m23;
	    m[3][0] = m30; m[3][1] = m31; m[3][2] = m32; m[3][3] = m33;
    }

    float* operator[](int i){
        return m[i];
    }

    
    const float* operator[](int i) const{
        return m[i];
    }

    union{
        float f[16];
        float m[4][4];
    };
};

#include <ostream>

inline std::ostream& operator<<(std::ostream &o, const mat4f &m){
#define fm std::setw(12)
    o << "mat4f[" << "\n" <<
    fm << m[0][0] << fm << m[0][1] << fm << m[0][2] << fm << m[0][3] << "\n" <<
    fm << m[1][0] << fm << m[1][1] << fm << m[1][2] << fm << m[1][3] << "\n" <<
    fm << m[2][0] << fm << m[2][1] << fm << m[2][2] << fm << m[2][3] << "\n" <<
    fm << m[3][0] << fm << m[3][1] << fm << m[3][2] << fm << m[3][3] << " ]" << "\n";
#undef fm
    return o;
};