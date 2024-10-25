#pragma once

/// <summary>
/// 3次元ベクトル
/// </summary>

class Vector3 {
public:
	float x;
	float y;
	float z;


	Vector3 operator*=(float s) {
		x *= s;
		y *= s;
		z *= s;
		return *this;
	}
	Vector3 operator-=(const Vector3& v) {
		x -= v.x;
		y -= v.y;
		z -= v.z;
		return *this;
	}
	Vector3 operator-=(const float& v) {
		x -= v;
		y -= v;
		z -= v;
		return *this;
	}
	Vector3 operator+=(const Vector3& v) {
		x += v.x;
		y += v.y;
		z += v.z;
		return *this;
	}
	Vector3 operator*=(const Vector3& v) {
		x *= v.x;
		y *= v.y;
		z *= v.z;
		return *this;
	}
	Vector3 operator+=(const float& v) {
		x += v;
		y += v;
		z += v;
		return *this;
	}
	Vector3 operator/=(float s) {
		x /= s;
		y /= s;
		z /= s;
		return *this;
	}

	Vector3 operator*(const int s) const {
		return Vector3{ x * s,y * s,z * s };
	}
	Vector3 operator*(const float other) const {
		return Vector3{ x * other,y * other,z * other };
	}
	Vector3 operator+(const Vector3& other) const {
		return Vector3{ x + other.x, y + other.y, z + other.z };
	}
	Vector3 operator-(const Vector3& other) const {
		return Vector3{ x - other.x, y - other.y, z - other.z };
	}
	Vector3 operator/(const int other) const {
		return Vector3{ x / other, y / other, z / other };
	}
	Vector3 operator/(const float other) const {
		return Vector3{ x / other, y / other, z / other };
	}

private:
};