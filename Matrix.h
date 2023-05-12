#pragma once

#include "Vector3.h"
#include"Matrix4x4.h"
#include<math.h>
#include <Novice.h>


class Matrix {
public:
	Matrix();
private:
	Vector3 scale;

	Vector3 rotate;

	Vector3 translate;

	Matrix4x4 ScaleMatrix;	

	Matrix4x4 TranslateMatrix;

	Matrix4x4 RotateMatrixXYZ;
	Matrix4x4 RotateMatrixX;
	Matrix4x4 RotateMatrixY;
	Matrix4x4 RotateMatrixZ;

public:

	Matrix4x4 perspectiveFovMatrix;
	//正射影行列
	Matrix4x4 orthographicMatrix;
	//ビューポート行列
	Matrix4x4 viewportMatrix;


public:
	void Update();


	Matrix4x4 MakeAffineMatrix(const Vector3& scale_, const Vector3& rot, const Vector3& translate_);
	Matrix4x4 MakeScaleMatrix(const Vector3& scale_);

	Matrix4x4 MakeRotateMatrixX(const Vector3& rot);
	Matrix4x4 MakeRotateMatrixY(const Vector3& rot);
	Matrix4x4 MakeRotateMatrixZ(const Vector3& rot);
	

	Matrix4x4 MakeTranslateMatrix(const Vector3& translate_);

	////積
	Matrix4x4 Multiply(const Matrix4x4& mat1, const Matrix4x4& mat2);

	//正規化
	Vector3 Normalize(const Vector3& v);

	//透視投影行列
	Matrix4x4 MakePerspectiveFovMatrix(float fovY, float aspectRatio, float nearClip, float farClip);
	//正射影行列
	Matrix4x4 MakeOrthographicMatrix(float left,float top ,float right, float bottom, float nearClip, float farClip);
	//ビューポート行列
	Matrix4x4 MakeViewportMatrix(float left, float top, float width, float height, float minDepth, float maxDepth);

};
