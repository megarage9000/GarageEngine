#pragma once

#include <array>
#include "GarageLinearAlgebra.h"

namespace GarageLinearAlgebra {

	// Defining typedefs here as PODS
	using Vector2 = std::array<float, 2>;
	using Vector3 = std::array<float, 3>;
	using Vector4 = std::array<float, 4>;
	using Matrix2 = std::array<float, 4>;
	using Matrix3 = std::array<float, 9>;
	using Matrix4 = std::array<float, 16>;

	// constexpr operations


	// --- Vector4 ---- 
	inline Vector4 operator* (const float& scalar, const Vector4& vector) {
		return Vector4 {
			vector[0] * scalar,
			vector[1] * scalar,
			vector[2] * scalar,
			vector[3] * scalar
		};
	}

	inline Vector4 operator* (const Vector4& vector, const float& scalar) {
		return scalar * vector;
	}

	inline Matrix4 operator*(const Vector4& vectorA, const Vector4& vectorB) {
		Matrix4 res;
		multiply_vectors(vectorA.data(), vectorB.data(), res.data(), 4, 16);
		return res;
	}

	inline Vector4 operator+(const Vector4& vectorA, const Vector4& vectorB) {
		Vector4 res;
		add_vectors(vectorA.data(), vectorB.data(), res.data(), 4);
		return res;
	}

	inline Vector4 operator-(const Vector4& vectorA, const Vector4& vectorB) {
		Vector4 res;
		subtract_vectors(vectorA.data(), vectorB.data(), res.data(), 4);
		return res;
	}

	// --- Vector3 ---
	inline Vector3 operator* (const float& scalar, const Vector3& vector) {
		return Vector3{
			vector[0] * scalar,
			vector[1] * scalar,
			vector[2] * scalar,
		};
	}

	inline Vector3 operator* (const Vector3& vector, const float& scalar) {
		return scalar * vector;
	}

	inline Matrix3 operator* (const Vector3& vectorA, const Vector3& vectorB) {
		Matrix3 res;
		multiply_vectors(vectorA.data(), vectorB.data(), res.data(), 3, 9);
		return res;
	}

	inline Vector3 operator+ (const Vector3& vectorA, const Vector3& vectorB) {
		Vector3 res;
		add_vectors(vectorA.data(), vectorB.data(), res.data(), 3);
		return res;
	}

	inline Vector3 operator- (const Vector3& vectorA, const Vector3& vectorB) {
		Vector3 res;
		subtract_vectors(vectorA.data(), vectorB.data(), res.data(), 3);
		return res;
	}

	// --- Vector 2 ---

	inline Vector2 operator * (const float& scalar, const Vector2& vector) {
		return Vector2{
			vector[0] * scalar,
			vector[1] * scalar
		};
	}

	inline Vector2 operator * (const Vector2& vector, const float& scalar) {
		return scalar * vector;
	}

	inline Matrix2 operator * (const Vector2& vectorA, const Vector2& vectorB) {
		Matrix2 res;
		multiply_vectors(vectorA.data(), vectorB.data(), res.data(), 2, 4);
		return res;
	}

	inline Vector2 operator + (const Vector2& vectorA, const Vector2& vectorB) {
		Vector2 res;
		add_vectors(vectorA.data(), vectorB.data(), res.data(), 2);
		return res;
	}

	inline Vector2 operator - (const Vector2& vectorA, const Vector2& vectorB) {
		Vector2 res;
		subtract_vectors(vectorA.data(), vectorB.data(), res.data(), 2);
		return res;
	}

	// --- Matrix type traits --- 
	template <typename Matrix>
	struct MatrixTraits {
		using Invalid = typename Matrix::InvalidMatrixError;
	};

	template <typename Matrix, typename Traits = MatrixTraits<Matrix>>
	float MatrixAt(const Matrix& matrix, const int& row, const int& col) {
		constexpr float dim = Traits::get_dimension();
		assert(row >= 0 && row < dim && col >= 0 && col < dim, "Invalid row / col for matrix");
		return matrix[row * dim + col];
	}

	template<typename Matrix, typename Traits = MatrixTraits<Matrix>>
	void MatrixSet(Matrix& matrix, const int& row, const int& col, const float& value) {
		constexpr float dim = Traits::get_dimension();
		assert(row >= 0 && row < dim && col >= 0 && col < dim, "Invalid row / col for matrix");
		matrix[row * dim + col] = value;
	}

	template<typename Matrix, typename Traits = MatrixTraits<Matrix>>
	Matrix Inverse(const Matrix& matrix) {
		constexpr float dim = Traits::get_dimension();
		Matrix res;
		if constexpr (dim == 4) {
			matrix4_inv(matrix, res);
		}

		else if constexpr (dim == 3) {
			matrix3_inv(matrix, res);
		}
		return res;
	}

	template<typename Matrix, typename Traits = MatrixTraits<Matrix>>
	Matrix Transpose(Matrix& matrix) {
		constexpr float dim = Traits::get_dimension();
		if constexpr (dim == 4) {
			transpose_matrix4(matrix);
		}

		else if constexpr (dim == 3) {
			transpose_matrix(matrix);
		}

	}

	template<typename Matrix, typename Traits = MatrixTraits<Matrix>>
	inline Matrix operator * (const Matrix& matrixA, const Matrix& matrixB) {
		constexpr float dim = Traits::get_dimension();
		Matrix res;
		
		if constexpr (dim == 4) {
			matrix4_multi(
				Traits::getData(matrixA),
				Traits::getData(matrixB),
				Traits::getData(res),
				4
			);
		}

		else if constexpr (dim == 3) {
			matrix3_multi(
				Traits::getData(matrixA),
				Traits::getData(matrixB),
				Traits::getData(res),
				3
			);
		}
		return res;
	}

	template <>
	struct MatrixTraits<Matrix4> {
		using Matrix = Matrix4;
		static constexpr int get_dimension() noexcept {
			return 4;
		}

		static float* getData(Matrix& matrix) {
			return matrix.data();
		}
	};

	template<>
	struct MatrixTraits<Matrix3> {
		using Matrix = Matrix3;
		static constexpr int get_dimension() noexcept {
			return 3;
		}
		
		static float* getData(Matrix& matrix) {
			return matrix.data();
		}
	};

	template<>
	struct MatrixTraits<Matrix2> {
		using Matrix = Matrix2;
		static constexpr int get_dimension() noexcept {
			return 2;
		}

		static float* getData(Matrix& matrix) {
			return matrix.data();
		}
	};

}


