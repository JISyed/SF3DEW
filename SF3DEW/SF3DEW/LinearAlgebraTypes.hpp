// Linear Algebra Types
// Typedefs for GLM data types for use in SF3DEW
//
// Written by Jibran Syed (4-4-2014)

#ifndef LINEAR_ALGEBRA_TYPES_H
#define LINEAR_ALGEBRA_TYPES_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/transform.hpp>

namespace sfew
{
	typedef glm::vec2 Vector2;
	typedef glm::vec3 Vector3;
	typedef glm::vec4 Vector4;
	typedef glm::mat2 Matrix2;
	typedef glm::mat3 Matrix3;
	typedef glm::mat4 Matrix4;

} // namespace sfew

#endif