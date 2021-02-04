#include "Vec3.h"
#include <math.h>
#include <iostream>


namespace EPIC{

	template<typename T>
	Vec3<T>::Vec3(){
		m_data[0] = 0.0f;
		m_data[1] = 0.0f;
		m_data[2] = 0.0f;
	}

	template<typename T>
	Vec3<T>::Vec3(T x, T y, T z){
		m_data[0] = x;
		m_data[1] = y;
		m_data[2] = z;
	}

	template<typename T>
	Vec3<T>::Vec3(const Vec3& v){
		m_data[0] = v[0];
		m_data[1] = v[1];
		m_data[2] = v[2];
	}


	template<typename T>
	const Vec3<T>& Vec3<T>::operator+(const Vec3<T>& v) const {

		Vec3<T>* res = new Vec3<T>(); // empty

		(*res)[0] = m_data[0]+v[0];
		(*res)[1] = m_data[1]+v[1];
		(*res)[2] = m_data[2]+v[2];

		return *res;
	}

	template<typename T>
	const Vec3<T>& Vec3<T>::operator-(const Vec3<T>& v)const {
		Vec3<T>* res = new Vec3<T>(); // empty

		(*res)[0] = m_data[0]-v[0];
		(*res)[1] = m_data[1]-v[1];
		(*res)[2] = m_data[2]-v[2];

		return *res;
	}

	template<typename T>
	const Vec3<T>& Vec3<T>::operator*(const float& k) const{

		Vec3<T>* res = new Vec3<T>(); // empty

		(*res)[0] = m_data[0]*k;
		(*res)[1] = m_data[1]*k;
		(*res)[2] = m_data[2]*k;

		return *res;

	}
	template<typename T>
	const Vec3<T>& Vec3<T>::operator/(const float& k) const{

		if(k==0){
			return *this;
		}

		Vec3<T>* res = new Vec3<T>(); // empty

		(*res)[0] = m_data[0]/k;
		(*res)[1] = m_data[1]/k;
		(*res)[2] = m_data[2]/k;

		return *res;
	}
	template<typename T>
	const Vec3<T>& Vec3<T>::operator+=(const Vec3<T>& v){
	
		m_data[0] += v[0];
		m_data[1] += v[1];
		m_data[2] += v[2];

		return *this;

	}

	template<typename T>
	const Vec3<T>& Vec3<T>::operator-=(const Vec3<T>& v){
	
		m_data[0] -= v[0];
		m_data[1] -= v[1];
		m_data[2] -= v[2];

		return *this;

	}

	template<typename T>
	const Vec3<T>& Vec3<T>::operator*=(const float& k){
	
		m_data[0] *= k;
		m_data[1] *= k;
		m_data[2] *= k;

		return *this;

	}


	template<typename T>
	const Vec3<T>& Vec3<T>::cross(const Vec3<T>& v) const{
		
		Vec3<T>* res = new Vec3<T>(); // empty

		(*res)[0] = m_data[1]*v[2]-m_data[2]*v[1];
		(*res)[1] = m_data[2]*v[0]-m_data[0]*v[2];
		(*res)[2] = m_data[0]*v[1]-m_data[1]*v[0];

		return *res;
	}



	template<typename T>
	float Vec3<T>::dot(const Vec3<T>& v) const{
		return m_data[0]*v[0]+
			   m_data[1]*v[1]+
			   m_data[2]*v[2];
	}



	template<typename T>
	T& Vec3<T>::operator[](int index){
		return m_data[index];
	}

	template<typename T>
	T Vec3<T>::operator[](int index) const{
		return m_data[index];
	}

	template<typename T>
	float Vec3<T>::norm() const{
		return sqrt(m_data[0]*m_data[0] +
					m_data[1]*m_data[1] +
					m_data[2]*m_data[2]);
	}

	template<typename T>
	const Vec3<T>& Vec3<T>::normalize() const{
		return *this/this->norm();
	}

}