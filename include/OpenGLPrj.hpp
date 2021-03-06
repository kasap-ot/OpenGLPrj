// Preprocessor Directives
#ifndef OpenGLPrj
#define OpenGLPrj
#pragma once

// System Headers
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

// Reference: https://github.com/nothings/stb/blob/master/stb_image.h#L4
// To use stb_image, add this in *one* C++ source file.
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

// Define Some Constants
const int SCR_WIDTH = 1000;
const int SCR_HEIGHT = 1000;

#endif //~ Glitter Header
