#include "Matrix.h"
Matrix::Matrix(){
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			ScaleMatrix.m[i][j] = 0.0f;
			TranslateMatrix.m[i][j] = 0.0f;
			RotateMatrixXYZ.m[i][j] = 0.0f;
			RotateMatrixX.m[i][j] = 0.0f;
			RotateMatrixY.m[i][j] = 0.0f;
			RotateMatrixZ.m[i][j] = 0.0f;
			perspectiveFovMatrix.m[i][j] = 0.0f;
			orthographicMatrix.m[i][j] = 0.0f;
			viewportMatrix.m[i][j] = 0.0f;
		}
	}

};

void Matrix::Update() {
	perspectiveFovMatrix = MakePerspectiveFovMatrix(0.63f, 1.33f, 0.1f, 1000.0f);
	orthographicMatrix = MakeOrthographicMatrix(-160.0f, 160.0f, 200.0f, 300.0f, 0.0f, 1000.0f);
	viewportMatrix = MakeViewportMatrix(100.0f, 200.0f, 600.0f, 300.0f, 0.0f, 1.0f);
}


////積
Matrix4x4 Matrix::Multiply(const Matrix4x4& mat1, const Matrix4x4& mat2) {
	Matrix4x4 result = {0.0f};
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			result.m[i][j] = mat1.m[i][0] * mat2.m[0][j] + mat1.m[i][1] * mat2.m[1][j] +
			                 mat1.m[i][2] * mat2.m[2][j] + mat1.m[i][3] * mat2.m[3][j];
		}
	}
	return result;
}


Matrix4x4 Matrix::MakeScaleMatrix(const Vector3& scale_){ 
	Matrix4x4 result{};
	result.m[0][0] = scale_.x;
	result.m[1][1] = scale_.y;
	result.m[2][2] = scale_.z;
	result.m[3][3] = 1.0f;
	return result;
}
Matrix4x4 Matrix::MakeRotateMatrixX(const Vector3& rot) {
	Matrix4x4 result{};
	result.m[0][0] = 1.0f;
	result.m[1][1] = cosf(rot.x);
	result.m[1][2] = sinf(rot.x);
	result.m[2][1] = -sinf(rot.x);
	result.m[2][2] = cosf(rot.x);
	result.m[3][3] = 1.0f;

	return result;
}

Matrix4x4 Matrix::MakeRotateMatrixY(const Vector3& rot) {
	Matrix4x4 result{};
	result.m[1][1] = 1.0f;
	result.m[0][0] = cosf(rot.y);
	result.m[0][2] = -sinf(rot.y);
	result.m[2][0] = sinf(rot.y);
	result.m[2][2] = cosf(rot.y);
	result.m[3][3] = 1.0f;
	return result;
}
Matrix4x4 Matrix::MakeRotateMatrixZ(const Vector3& rot) {
	Matrix4x4 result{};
	result.m[2][2] = 1.0f;
	result.m[0][0] = cosf(rot.z);
	result.m[0][1] = sinf(rot.z);
	result.m[1][0] = -sinf(rot.z);
	result.m[1][1] = cosf(rot.z);
	result.m[3][3] = 1.0f;
	return result;
}
Matrix4x4 Matrix::MakeTranslateMatrix(const Vector3& translate_) {
	Matrix4x4 result{};
	result.m[0][0] = 1.0f;
	result.m[1][1] = 1.0f;
	result.m[2][2] = 1.0f;
	result.m[3][3] = 1.0f;

	result.m[3][0] = translate_.x;
	result.m[3][1] = translate_.y;
	result.m[3][2] = translate_.z;
	return result;

}

Matrix4x4
    Matrix::MakeAffineMatrix(const Vector3& scale_, const Vector3& rot, const Vector3& translate_) {
	Matrix4x4 result{};

	//スケーリング行列の作成
	ScaleMatrix = MakeScaleMatrix(scale_);
	//X,Y,Z軸の回転行列の作成
	RotateMatrixX = MakeRotateMatrixX(rot);
	RotateMatrixY = MakeRotateMatrixY(rot);
	RotateMatrixZ = MakeRotateMatrixZ(rot);
	//回転行列の結合
	RotateMatrixXYZ = Multiply(RotateMatrixX, Multiply(RotateMatrixY, RotateMatrixZ));
	//平行移動行列の作成
	TranslateMatrix = MakeTranslateMatrix(translate_);

	result = Multiply(ScaleMatrix, Multiply(RotateMatrixXYZ, TranslateMatrix));

	return result;

}


Vector3 Matrix::Normalize(const Vector3& v) {
	Vector3 result{0, 0, 0};
	float bulletNorm = static_cast<float>(sqrt((v.x * v.x) + (v.y * v.y) + (v.z * v.z)));

	if (bulletNorm != 0.0f) {

		result = {
		    (v.x / bulletNorm),
			(v.y / bulletNorm),
		    (v.z / bulletNorm)
		};
	}

	return result;

}

Matrix4x4 Matrix::MakePerspectiveFovMatrix(float fovY, float aspectRatio, float nearClip, float farClip) {
	Matrix4x4 result{ 0 };

	result.m[0][0] = (1.0f / aspectRatio) * (1.0f / tanf(fovY / 2.0f));
	result.m[1][1] = (1.0f / tanf(fovY / 2.0f));
	result.m[2][2] = farClip / (farClip - nearClip);
	result.m[2][3] = 1.0f;
	result.m[3][2] = (-nearClip * farClip) / (farClip - nearClip);

	return result;
}

Matrix4x4 Matrix::MakeOrthographicMatrix(float left,float top ,float right, float bottom, float nearClip, float farClip) {
	Matrix4x4 result{ 0 };

	result.m[0][0] = 2.0f / (right - left);
	result.m[1][1] = 2.0f / (top - bottom);
	result.m[2][2] = 1.0f / (farClip - nearClip);
	result.m[3][0] = (left + right) / (left - right);
	result.m[3][1] = (top + bottom) / (bottom - top);
	result.m[3][2] = nearClip / (nearClip - farClip);
	result.m[3][3] = 1.0f;

	return result;
}

Matrix4x4 Matrix::MakeViewportMatrix(float left, float top, float width, float height, float minDepth, float maxDepth) {
	Matrix4x4 result{ 0 };

	result.m[0][0] = width / 2.0f;
	result.m[1][1] = -(height / 2.0f);
	result.m[2][2] = maxDepth - minDepth;
	result.m[3][0] = left + (width / 2.0f);
	result.m[3][1] = top + (height / 2.0f);
	result.m[3][2] = minDepth;
	result.m[3][3] = 1.0f;

	return result;
}