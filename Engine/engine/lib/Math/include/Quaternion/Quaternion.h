#ifndef QUATERNION_H
#define QUATERNION_H

#include <string>

namespace gnLib {

	class Vector3;
	class Matrix4x4;

	class Quaternion {
	public:

		/// <summary>
		/// 単位クォータニオンを作成する
		/// </summary>
		/// <returns> 単位クォータニオン </returns>
		static Quaternion identity();

		/// <summary>
		/// 任意の軸に回転した回転クォータニオンを作成する。
		/// </summary>
		/// <param name="_axis"> 回転軸を表す3Dベクトル </param>
		/// <param name="_angle"> 
		/// ラジアン単位の回転角。
		/// 回転軸を原点に向かって見たとき、時計通りに回転する。
		/// </param>
		/// <returns> 回転クォータニオン </returns>
		static Quaternion rotationAxis(const Vector3& _axis, float _angle);

		/// <summary>
		/// 回転行列から回転クォータニオンを作成する。
		/// </summary>
		/// <param name="_m"> 回転行列 </param>
		/// <returns> 回転クォータニオン </returns>
		static Quaternion rotationMatrix(const Matrix4x4& _m);

		/// <summary>
		/// ピッチ、ヨー、ロール(オイラー角)に基づいて回転クォータニオンを作成する。
		/// 回転の順番は、ロール(Z)、ピッチ(X)、ヨー(Z)の順番で回転する。
		/// </summary>
		/// <param name="_pitch"> x軸周りの回転角 </param>
		/// <param name="_yaw"> y軸周りの回転角 </param>
		/// <param name="_roll"> y軸周りの回転角 </param>
		/// <returns> 回転クォータニオン </returns>
		static Quaternion rotationRollPitchYaw(float _pitch, float _yaw, float _roll);

		/// <summary>
		/// ピッチ、ヨー、ロール(オイラー角)を含むベクトル基づいて回転クォータニオンを作成する。
		/// 回転の順番は、ロール(Z)、ピッチ(X)、ヨー(Z)の順番で回転する。
		/// </summary>
		/// <param name="_angles"> ピッチ、ヨー、ロール(オイラー角)を含むベクトル </param>
		/// <returns> 回転クォータニオン </returns>
		static Quaternion rotationRollPitchYaw(const Vector3& _angles);

		// static Quaternion euler(float _x, float _y, float _z);

	public:
		Quaternion(float _x, float _y, float _z, float _w);
		~Quaternion() = default;

		/// <summary>
		/// クォータニオンの大きさを計算する。
		/// </summary>
		/// <returns> クォータニオンの大きさ </returns>
		const float length();

		/// <summary>
		/// クォータニオンの大きさの2乗を計算する。
		/// </summary>
		/// <returns> クォータニオンの大きさの2乗 </returns>
		const float sqrtLength();

		/// <summary>
		/// クォータニオンを正規化します。
		/// </summary>
		/// <returns> 正規化されたクォータニオン </returns>
		Quaternion normalized();

		/// <summary>
		/// 共役クォータニオン
		/// </summary>
		/// <returns> 共役クォータニオン </returns>
		Quaternion conjugate();

		/// <summary>
		/// 逆クォータニオン
		/// </summary>
		/// <returns> 逆クォータニオン </returns>
		Quaternion inverse();

		/// <summary>
		/// クォータニオンから回転行列を作成します。
		/// </summary>
		/// <returns> 回転行列 </returns>
		Matrix4x4 toMatrix();

		/// <summary>
		/// クォータニオンの内積
		/// </summary>
		/// <param name="_q"> クォータニオン </param>
		/// <returns> クォータニオンの内積 </returns>
		const float dot(const Quaternion& _q);

		const Quaternion operator* (const Quaternion& _q) const;

		const Quaternion operator*= (const Quaternion& _q);

		const bool operator== (const Quaternion& _q) const;

		const bool operator!= (const Quaternion& _q) const;

		const std::string toString();

	public:
		float x;
		float y;
		float z;
		float w;
	};

}

#endif // !QUATERNION_H
