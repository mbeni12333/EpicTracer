#pragma once
#include <iostream>


namespace EPIC{

	template <typename T> class Vec3{
		public:

		Vec3<T>();
		Vec3<T>(T x, T y, T z);
		Vec3<T>(const Vec3& v);

		const Vec3<T>& operator+(const Vec3<T>& v) const;
		const Vec3<T>& operator-(const Vec3<T>& v) const;
		const Vec3<T>& operator*(const float& k) const;
		const Vec3<T>& operator/(const float& k) const;
		const Vec3<T>& operator+=(const Vec3<T>& v);
		const Vec3<T>& operator-=(const Vec3<T>& v);
		const Vec3<T>& operator*=(const float& v);

		T& operator[](int index);
		T operator[](int index) const;

		const Vec3<T>& cross(const Vec3<T>& v) const;

		float norm()  const;
		const Vec3<T>& normalize() const;
		float dot(const Vec3<T>& v) const;
		 

		protected:
		T m_data[3];


	};



	template<typename T>
	std::ostream& operator<< (std::ostream& out, Vec3<T>& v){
		out<<v[0]<<" "<<v[1]<<" "<<v[2]<<std::endl;
		return out;
	}

}



