#pragma once
#include<Matrix4x4.h>
#include <Vector3.h>
#include <assert.h>
#include <cmath>
#include <math.h>
#define N 4 // 逆行列を求める行列の行数・列数
int check(double mat[N][N], double inv[N][N]);
// 行列の加法
Matrix4x4 Add(const Matrix4x4& m1, const Matrix4x4& m2);
// 行列の減法
Matrix4x4 Subtract(const Matrix4x4& m1, const Matrix4x4& m2);
Vector3 Subtract(const Vector3& v1, const Vector3& v2);
// 転置行列
Matrix4x4 Transpose(const Matrix4x4& m);
// 単位行列の作成
Matrix4x4 MakeIdentity4x4();
// 行列の積
Matrix4x4 Multiply(const Matrix4x4& m1, const Matrix4x4& m2);
// １．平行移動行列
Matrix4x4 MakeTranslateMatrix(const Vector3& translate);
// ２．拡大縮小行列
Matrix4x4 MakeScaleMatrix(const Vector3& scale);
// ３．座標変換
Vector3 Transform(const Vector3& vector, const Matrix4x4& matrix);
// ４．X軸回転行列
Matrix4x4 MakeRotateXMatrix(float radian);
// ５．Y軸回転行列
Matrix4x4 MakeRotateYMatrix(float radian);
// ６．Z軸回転行列
Matrix4x4 MakeRotateZMatrix(float radian);
// 3次元アフィン変換行列
Matrix4x4 MakeAffineMatrix(const Vector3& scale, const Vector3& rotate, const Vector3& translate);
// 透視投影行列
Matrix4x4 MakePerspectiveFovMatrix(float fovY, float aspectRatio, float nearClip, float farClip);

// 正射影行列
Matrix4x4 MakeOrthographicMatrix(float left, float top, float right, float bottom, float nearClip, float farClip);

// ビューポート変換行列
Matrix4x4 MakeViewportMatrix(float left, float top, float width, float height, float minDepth, float maxDepth);
// 逆行列
Matrix4x4 Inverse(const Matrix4x4& m);
static const int kRowHeight = 20;
static const int kColumnWidth = 60;

Vector3 Cross(const Vector3& v1, const Vector3& v2);
float Dot(const Vector3& v1, const Vector3& v2);