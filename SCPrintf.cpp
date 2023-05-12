#include "SCPrintf.h"
SCPrintf::SCPrintf() {
	matrix = new Matrix;

	kRowHeight = 20;
	kColumnWidth = 60;
}

SCPrintf::~SCPrintf() {
	delete matrix;
}

void SCPrintf::MatrixScreenPrintf(int x, int y, const Matrix4x4& mat, const char* label) {
	Novice::ScreenPrintf(x, y, "%s", label);

	for (int row = 0; row < 4; row++) {
		for (int column = 0; column < 4; column++) {
			Novice::ScreenPrintf(x + column * kColumnWidth, y + row * kRowHeight + kRowHeight, "%0.2f", mat.m[row][column]);
		}
	}
}

void SCPrintf::VectorScreenPrintf(int x, int y, const Vector3& vec, const char* label) {

	Novice::ScreenPrintf(x, y, "%0.2f  %0.2f  %0.2f", vec.x, vec.y, vec.z);
	Novice::ScreenPrintf(x+kColumnWidth*3, y, "%s", label);

}

void SCPrintf::Update() {
	matrix->Update();
	MatrixScreenPrintf(0, 0, matrix->orthographicMatrix, "OrthographicMatrix");
	MatrixScreenPrintf(0, kRowHeight * 5, matrix->perspectiveFovMatrix, "perspectiveFovMatrix");
	MatrixScreenPrintf(0, kRowHeight * 10, matrix->viewportMatrix, "viewportMatrix");	
}