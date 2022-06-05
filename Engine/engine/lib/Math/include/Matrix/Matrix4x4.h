#ifndef MATRIX4X4_H
#define MATRIX4X4_H

#include <string>

namespace gnLib {

	class Vector3;

	class Matrix4x4 {
	public:

		/// <summary>
		/// 単位行列を作成する。
		/// </summary>
		/// <returns> 単位行列 </returns>
		static Matrix4x4 identity();

		/// <summary>
		/// x軸を軸とした回転行列を作成する。
		/// </summary>
		/// <param name="_angle"> 
		/// ラジアン単位の回転角。
		/// 回転軸を原点に向かって見たとき、時計通りに回転する。
		/// </param>
		/// <returns> x軸の回転行列 </returns>
		static Matrix4x4 rotationX(float _angle);

		/// <summary>
		/// y軸を軸とした回転行列を作成する。
		/// </summary>
		/// <param name="_angle">
		/// ラジアン単位の回転角。
		/// 回転軸を原点に向かって見たとき、時計通りに回転する。
		/// </param>
		/// <returns> y軸の回転行列 </returns>
		static Matrix4x4 rotationY(float _angle);

		/// <summary>
		/// z軸を軸とした回転行列を作成する。
		/// </summary>
		/// <param name="_angle">
		/// ラジアン単位の回転角。
		/// 回転軸を原点に向かって見たとき、時計通りに回転する。
		/// </param>
		/// <returns> z軸の回転行列 </returns>
		static Matrix4x4 rotationZ(float _angle);

		/// <summary>
		/// ピッチ、ヨー、ロール(オイラー角)に基づいて回転行列を作成する。
		/// 回転の順番は、ロール(Z)、ピッチ(X)、ヨー(Z)の順番で回転する。
		/// </summary>
		/// <param name="_pitch"> x軸周りの回転角 </param>
		/// <param name="_yaw"> y軸周りの回転角 </param>
		/// <param name="_roll"> z軸周りの回転角 </param>
		/// <returns> 回転行列 </returns>
		static Matrix4x4 rotationRollPitchYaw(float _pitch, float _yaw, float _roll);

		/// <summary>
		/// ピッチ、ヨー、ロール(オイラー角)を含むベクトル基づいて回転クォータニオンを作成する。
		/// 回転の順番は、ロール(Z)、ピッチ(X)、ヨー(Z)の順番で回転する。
		/// </summary>
		/// <param name="_angles"> ピッチ、ヨー、ロール(オイラー角)を含むベクトル </param>
		/// <returns> 回転行列 </returns>
		static Matrix4x4 rotationRollPitchYaw(const class Vector3& _angles);

		/// <summary>
		/// x軸、y軸、z軸に沿った拡大・縮小行列を作成する。
		/// </summary>
		/// <param name="_scallX"> x軸に沿った倍率 </param>
		/// <param name="_scallY"> y軸に沿った倍率 </param>
		/// <param name="_scallZ"> z軸に沿った倍率 </param>
		/// <returns> スケーリング行列 </returns>
		static Matrix4x4 scaling(float _scallX, float _scallY, float _scallZ);

		/// <summary>
		///  x軸、y軸、z軸を含むベクトルも基づいて拡大・縮小行列を作成する。
		/// </summary>
		/// <param name="_scall"> 拡大・縮小を含むベクトル </param>
		/// <returns> スケーリング行列 </returns>
		static Matrix4x4 scaling(const class Vector3& _scall);

		/// <summary>
		/// 平行移動された変換行列を作成する。
		/// </summary>
		/// <param name="_offsetX"> x軸に沿った平行移動 </param>
		/// <param name="_offsetY"> y軸に沿った平行移動 </param>
		/// <param name="_offsetZ"> z軸に沿った平行移動 </param>
		/// <returns> 平行移動された変換行列 </returns>
		static Matrix4x4 translation(float _offsetX, float _offsetY, float _offsetZ);

		/// <summary>
		/// 平行移動された変換行列を作成する。
		/// </summary>
		/// <param name="_offset"> x軸、y軸、z軸を含むベクトル </param>
		/// <returns> 平行移動された変換行列 </returns>
		static Matrix4x4 translation(const class Vector3& _offset);

		/// <summary>
		/// 左手座標系を基準とし、カメラの位置、上方向、焦点をを使用して、ビュー行列を作成する。
		/// </summary>
		/// <param name="_eye"> カメラの位置 </param>
		/// <param name="_focus"> カメラの焦点 </param>
		/// <param name="_up"> カメラの上方向 </param>
		/// <returns> ビュー行列 </returns>
		static Matrix4x4 lookAtLH(const Vector3& _eye, const Vector3& _focus, const Vector3& _up);

		/// <summary>
		/// 左手座標系の正射影行列を作成する。
		/// </summary>
		/// <param name="_viewWidth"> クリッピング平面の錐台の幅 </param>
		/// <param name="_viewHeight"> クリッピング平面の錐台の高さ </param>
		/// <param name="_nearZ"> 近くのクリッピング平面の距離 </param>
		/// <param name="_farZ"> 遠くのクリッピング平面の距離 </param>
		/// <returns> 正射影行列 </returns>
		static Matrix4x4 orthographicLH(float _viewWidth, float _viewHeight, float _nearZ, float _farZ);

		/// <summary>
		/// 左手座標系の透視投影行列を作成する。
		/// </summary>
		/// <param name="_fovAngleY"> 視野角(ラジアン単位) </param>
		/// <param name="_aspectRatio"> アスペクト比 </param>
		/// <param name="_nearZ"> 近くのクリッピング平面の距離(0より大きくなければならない) </param>
		/// <param name="_farZ"> 遠くのクリッピング平面の距離(0より大きくなければならない)  </param>
		/// <returns> 透視投影行列 </returns>
		static Matrix4x4 perspectiveFovLH(float _fovAngleY, float _aspectRatio, float _nearZ, float _farZ);

		/// <summary>
		/// 左手座標系の透視投影行列を作成する。
		/// </summary>
		/// <param name="_viewWidth"> クリッピング平面の錐台の幅 </param>
		/// <param name="_viewHeight"> クリッピング平面の錐台の高さ </param>
		/// <param name="_nearZ"> 近くのクリッピング平面の距離 </param>
		/// <param name="_farZ"> 遠くのクリッピング平面の距離 </param>
		/// <returns> 透視投影行列 </returns>
		static Matrix4x4 perspectiveLH(float _viewWidth, float _viewHeight, float _nearZ, float _farZ);

	public:
		Matrix4x4();
		Matrix4x4(const Matrix4x4& _m);
		Matrix4x4(
			float _m00, float _m01, float _m02, float _m03,
			float _m10, float _m11, float _m12, float _m13,
			float _m20, float _m21, float _m22, float _m23,
			float _m30, float _m31, float _m32, float _m33
		);
		Matrix4x4(const float _m[16]);
		~Matrix4x4() = default;

		/// <summary>
		/// 行列式を計算する。
		/// </summary>
		/// <returns> 行列式 </returns>
		float determinant();

		/// <summary>
		/// 逆行列を計算する。
		/// </summary>
		void inverse();

		/// <summary>
		/// 行列を転置行列にする。
		/// </summary>
		void transpose();

		const Matrix4x4 operator+(const Matrix4x4& _m) const;

		const Matrix4x4 operator-(const Matrix4x4& _m) const;

		const Matrix4x4 operator*(const Matrix4x4& _m) const;
		const Matrix4x4 operator*(float _scalar) const;
		const friend Matrix4x4 operator*(float _scalar, const Matrix4x4& _m);

		const Matrix4x4& operator+=(const Matrix4x4& _m);

		const Matrix4x4& operator-=(const Matrix4x4& _m);

		const Matrix4x4& operator*=(const Matrix4x4& _m);

		const bool operator==(const Matrix4x4& _m) const;

		const bool operator!=(const Matrix4x4& _m) const;

		const std::string toString();

	public:
		union {
			float m[4][4];

			struct {
				float m00, m01, m02, m03;
				float m10, m11, m12, m13;
				float m20, m21, m22, m23;
				float m30, m31, m32, m33;
			};
		};
	};

}

#endif // !MATRIX4X4_H