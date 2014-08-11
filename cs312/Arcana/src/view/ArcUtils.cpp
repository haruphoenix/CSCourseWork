#include "ArcUtils.h"
#include <math.h>
//#include <time.h>
#include <GL/glew.h>
#include <stdlib.h>
#include <stdio.h>
			      
void ExitOnGLError(const char* errorMessage)
{
  const GLenum ErrorValue = glGetError();

  if (ErrorValue != GL_NO_ERROR)
  {
    fprintf(stderr, "%s: %s\n", errorMessage, gluErrorString(ErrorValue));
    exit(EXIT_FAILURE);
  }
}

GLuint LoadShader(const char* filename, GLenum shaderType)
{
  GLuint shaderID = 0;
  FILE* file;
  long fileSize = -1;
  char* glslSource;

  if (NULL != (file = fopen(filename, "rb")) &&
      0 == fseek(file, 0, SEEK_END) &&
      -1 != (fileSize = ftell(file)))
  {
    rewind(file);

    if (NULL != (glslSource = (char*)malloc(fileSize + 1)))
    {
      if (fileSize == (long)fread(glslSource, sizeof(char), fileSize, file))
      {
	glslSource[fileSize] = '\0';

	if (0 != (shaderID = glCreateShader(shaderType)))
	  {                            // Must be cast
	  glShaderSource(shaderID, 1, (const char **)&glslSource, NULL);
	  glCompileShader(shaderID);
	  ExitOnGLError("Could not compile a shader");
	}
	else
	  fprintf(stderr, "ERROR: Could not create a shader.\n");
      }
      else
	fprintf(stderr, "ERROR: Could not read file %s\n", filename);

      free(glslSource);
    }
    else
      fprintf(stderr, "ERROR: Could not allocate %i bytes.\n", (int)fileSize);

    fclose(file);
  }
  else
  {
    if (NULL != file)
      fclose(file);
    fprintf(stderr, "ERROR: Could not open file %s\n", filename);
  }

  return shaderID;
}
