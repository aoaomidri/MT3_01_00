#pragma once
#include"Matrix.h"
class SCPrintf
{
public:
	SCPrintf();
	~SCPrintf();

private:
	Matrix* matrix;
	int kRowHeight;
	int kColumnWidth;

public:
	void MatrixScreenPrintf(int x, int y, const Matrix4x4& mat, const char* label);

	void VectorScreenPrintf(int x, int y, const Vector3& vec, const char* label);

	void Update();
};

