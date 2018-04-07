#pragma once


struct Matrix2 {
	float _11, _12;
	float _21, _22;

	Matrix2() {};
	Matrix2(float m11, float m12, float m21, float m22) {
		_11 = m11;
		_12 = m12;
		_21 = m21;
		_22 = m22;
	};

	void SetScale(float a, float b) {  // 배수 행렬
		SetIdentity();
		_11 = a;
		_22 = b;
	};

	void SetIdentity() {				// 단위 행렬
		_11 = 1.0f;
		_12 = 0.0f;
		_21 = 0.0f;
		_22 = 1.0f;
	};

	void SetRotate(float degree) {
		float Radian = Deg2Rad(degree);

		_11 = cosf(Radian);
		_12 = -sinf(Radian);
		_21 = sinf(Radian);
		_22 = cosf(Radian);
	}

	Matrix2 operator *(const Matrix2 Other) const; // 행렬연산
};


struct Matrix3
{
public:
	float _11, _12, _13;
	float _21, _22, _23;
	float _31, _32, _33;

	Matrix3() {
		_11 = 1.0f;
		_12 = 0.0f;
		_13 = 0.0f;

		_21 = 0.0f;
		_22 = 1.0f;
		_23 = 0.0f;

		_31 = 0.0f;
		_32 = 0.0f;
		_33 = 1.0f;
	}

	Matrix3(float m11, float m12, float m13, float m21, float m22, float m23, float m31, float m32, float m33) {
		_11 = m11;
		_12 = m12;
		_13 = m13;

		_21 = m21;
		_22 = m22;
		_23 = m23;

		_31 = m31;
		_32 = m32;
		_33 = m33;
	}

	void SetTranslation(float InX, float InY) {
		SetIndentity();
		_13 = InX;
		_23 = InY;
	}

	void SetScale(float a, float b,float c) {
		SetIndentity();
		_11 = a;
		_22 = b;
		_33 = c;
	}

	void SetIndentity() {
		_11 = 1.0f;
		_12 = 0.0f;
		_13 = 0.0f;

		_21 = 0.0f;
		_22 = 1.0f;
		_23 = 0.0f;

		_31 = 0.0f;
		_32 = 0.0f;
		_33 = 1.0f;
	}

	void SetRotation(float degree) {

		float Radian = Deg2Rad(degree);

		_11 = cosf(Radian);
		_12 = -sinf(Radian);
		_13 = 0.0f;

		_21 = sinf(Radian);
		_22 = cosf(Radian);
		_23 = 0.0f;

		_31 = 0.0f;
		_32 = 0.0f;
		_33 = 1.0f;
	}

	Matrix3 operator *(const Matrix3 Other) const; 
};

