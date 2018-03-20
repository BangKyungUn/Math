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