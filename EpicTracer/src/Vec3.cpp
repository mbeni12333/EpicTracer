#include "Vec3.h"
#include <math.h>
#include <iostream>


namespace EPIC{

	template<typename T>
	Vec3<T>::Vec3():m_data{0.0f, 0.0f, 0.0f}{}

	template<typename T>
	Vec3<T>::Vec3(T x, T y, T z) : m_data{x, y, z}{}

	template<typename T>
	Vec3<T>::Vec3(const Vec3<T>& v){
		m_data[0] = v[0];
		m_data[1] = v[1];
		m_data[2] = v[2];
	}


	template<typename T>
	std::shared_ptr<Vec3<T>> Vec3<T>::operator+(const Vec3<T>& v) const {

		auto res =std::make_shared<Vec3<T>>(m_data[0]+v[0],
											m_data[1]+v[1],
											m_data[2]+v[2]);

		return res;
	}

	template<typename T>
	std::shared_ptr<Vec3<T>> Vec3<T>::operator-(const Vec3<T>& v)const {
		auto res =std::make_shared<Vec3<T>>(); // empty

		(*res)[0] = m_data[0]-v[0];
		(*res)[1] = m_data[1]-v[1];
		(*res)[2] = m_data[2]-v[2];

		return res;
	}

	template<typename T>
	std::shared_ptr<Vec3<T>> Vec3<T>::operator*(const float& k) const{

		auto res =std::make_shared<Vec3<T>>(); // empty

		(*res)[0] = m_data[0]*k;
		(*res)[1] = m_data[1]*k;
		(*res)[2] = m_data[2]*k;

		return res;

	}
	template<typename T>
	std::shared_ptr<Vec3<T>> Vec3<T>::operator/(const float& k) const{

		if(k==0){
			return this;
		}

		auto res = std::make_shared<Vec3<T>>(); // empty

		(*res)[0] = m_data[0]/k;
		(*res)[1] = m_data[1]/k;
		(*res)[2] = m_data[2]/k;

		return res;
	}
	template<typename T>
	std::shared_ptr<Vec3<T>> Vec3<T>::operator+=(const Vec3<T>& v){
	

		auto res = std::make_shared<Vec3<T>>(); // empty

		(*res)[0] = m_data[0]+v[0];
		(*res)[1] = m_data[1]+v[1];
		(*res)[2] = m_data[2]+v[2];

		return res;

		/*m_data[0] += v[0];
		m_data[1] += v[1];
		m_data[2] += v[2];

		return std::dynamic_pointer_cast<<Vec3<T>>(this);*/

	}

	template<typename T>
	std::shared_ptr<Vec3<T>> Vec3<T>::operator-=(const Vec3<T>& v){
	
		auto res = std::make_shared<Vec3<T>>(); // empty

		(*res)[0] = m_data[0]-v[0];
		(*res)[1] = m_data[1]-v[1];
		(*res)[2] = m_data[2]-v[2];

		return res;

	}

	template<typename T>
	std::shared_ptr<Vec3<T>> Vec3<T>::operator*=(const float& k){
	
		auto res = std::make_shared<Vec3<T>>(); // empty

		(*res)[0] = m_data[0]*k;
		(*res)[1] = m_data[1]*k;
		(*res)[2] = m_data[2]*k;

		return res;
	}


	template<typename T>
	std::shared_ptr<Vec3<T>> Vec3<T>::cross(const Vec3<T>& v) const{
		
		auto res = std::make_shared<Vec3<T>>(); // empty

		(*res)[0] = m_data[1]*v[2]-m_data[2]*v[1];
		(*res)[1] = m_data[2]*v[0]-m_data[0]*v[2];
		(*res)[2] = m_data[0]*v[1]-m_data[1]*v[0];

		return res;
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


		return sqrt((m_data[0])*(m_data[0])+
					(m_data[1])*(m_data[1])+
					(m_data[2])*(m_data[2]));
	}

	template<typename T>
	std::shared_ptr<Vec3<T>> Vec3<T>::normalize() {
		float x = m_data[0]/this->norm();
		float y = m_data[1]/this->norm();
		float z = m_data[2]/this->norm();
		auto res = std::make_shared<Vec3<T>>(x, y, z);

		return res;
	}

}