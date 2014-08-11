// Multiplies two 4x4 matrices together
function multiply4by4(m1, m2)
{
   var m3 = new Array();
   for (var i = 0; i < 16; i++)
   {
      m3[i] = matrixDotProduct(m1, m2, Math.floor(i * .25), i % 4);
   }
   return m3;
}

// Does matrix multiplication of a matrix and a vector
function multiplyVector(m1, v1)
{
   var v2 = new Array();
   for (var i = 0; i < 4; i++)
   {
      v2[i] = vectorDotProduct(m1, v1, i);
   }
   return v2;
}

// Computes a dot product of a given row and column
function matrixDotProduct(m1, m2, r, c)
{
   var sum = 0;
   for (var i = 0; i < 4; i++)
   {
      sum += m1[(4 * r) + i] * m2[(4 * i) + c];
   }
   return sum;
}

// Dot Product for vectors
function vectorDotProduct(m1, v1, r)
{
   var sum = 0;
   for (var i = 0; i < 4; i++)
   {
      sum += m1[(4 * r) + i] * v1[i];
   }
   return sum;
}

// Add two vectors
function addVector(v1, v2)
{
   return [v1[0] + v2[0],
           v1[1] + v2[1],
           v1[2] + v2[2],
                 1     ];
}

// Subtract two vectors
function subtractVector(v1, v2)
{
   return [v1[0] - v2[0],
           v1[1] - v2[1],
           v1[2] - v2[2],
                 1     ];
}

// Add two matrices
function addMatrix(m1, m2)
{
   return [m1[0]  +  m2[0],  m1[1] +  m2[1],  m1[2] +  m2[2],  m1[3] +  m2[3],
           m1[4]  +  m2[4],  m1[5] +  m2[5],  m1[6] +  m2[6],  m1[7] +  m2[7],
           m1[8]  +  m2[8],  m1[9] +  m2[9], m1[10] + m2[10], m1[11] + m2[11],
           m1[12] + m2[12], m1[13] + m2[13], m1[14] + m2[14],        1      ];
}

// Subtract two matrices
function subtractMatrix(m1, m2)
{
   return [m1[0]  -  m2[0],  m1[1] -  m2[1],  m1[2] -  m2[2],  m1[3] -  m2[3],
           m1[4]  -  m2[4],  m1[5] -  m2[5],  m1[6] -  m2[6],  m1[7] -  m2[7],
           m1[8]  -  m2[8],  m1[9] -  m2[9], m1[10] - m2[10], m1[11] - m2[11],
           m1[12] - m2[12], m1[13] - m2[13], m1[14] - m2[14],        1      ];
}

// Multiply every value in a vector by a scalar.
function multiplyScalar(v, s)
{
   for (var i = 0; i < v.length - 1; i++) v[i] *= s;
}

// Find the magnitude
function getMagnitude(v)
{
   return Math.sqrt(vectorDotProduct(v, v, 0));
}

// Normalize
function vectorNormalize(v)
{
   var length = getMagnitude(v);
   if (length > 0.0001)
   {
      var iLength = 1 / length;
      multiplyScalar(v, iLength);
      return true;
   }
   else return false;
}

// Find the angle between two vectors
function findAngle(v1, v2)
{
   return Math.arccos(vectorDotProduct(v1, v2, 0) / (getMagnitude(v1) * getMagnitude(v2)));
}


// Find the cross product of two vectors
function crossProduct(v1, v2)
{
   return [(v1[1] * v2[2]) - (v1[2] * v2[1]),
           (v1[2] * v2[0]) - (v1[0] * v2[2]),
           (v1[0] * v2[1]) - (v1[1] * v2[0]),
                           1               ];
}

// Constructs a plane and returns the distance. The direction the normal is facing.
// Credit to www.gamedev.net/page/resource/_/technical/graphics-programming-and-theory/
// the-world-of-3-d-graphics-part-2-vectors-and-p-r1443 for c++ example and explanation
function getDirection(v1, v2, v3)
{
   var norm = crossProduct(subtractVector(v3, v2), subtractVector(v1, v2));
   if (norm[2] < 0) return false;
   else return true;
}

// Prints a 4x4 matrix
function printMatrix(m)
{
   console.log("Matrix\n------");
   dim = Math.sqrt(m.length);
   for (var i = 0; i < dim; i++)
   {
      var line = "";
      for (var j = 0; j < dim; j++)
      {
         line += m[(i * dim) + j] + " ";
      }
      console.log(line + "\n");
   }
   console.log("\n");
}

// Prints a vector
function printVector(v)
{
   console.log("Vector\n------");
   var line = "";
   for (var i = 0; i < 4; i++)
   {
      line += v[i] + " ";
   }
   line += "\n";
   console.log(line);
}

// Prints a vector
function printVerts(v)
{
   console.log("Vector\n------");
   for (var i = 0; i < 4; i++)
   {
      console.log(v[i][0]);
   }
}

var radScaler = Math.PI / 180;

// Returns a matrix that will rotate an object by x degrees
function getZRotationMatrix(degree)
{
   var rMatrix = [
                   1, 0, 0, 0,
                   0, 1, 0, 0,
                   0, 0, 1, 0,
                   0, 0, 0, 1 ];
   var rad = degree * radScaler;
   var sin = Math.sin(rad);
   var cos = Math.cos(rad);
   rMatrix[0] = cos;
   rMatrix[1] = -sin;
   rMatrix[4] = sin;
   rMatrix[5] = cos;
   return rMatrix;
}

// Returns a matrix that will rotate an object by x degrees
function getXRotationMatrix(degree)
{
   var rMatrix = [
                   1, 0, 0, 0,
                   0, 1, 0, 0,
                   0, 0, 1, 0,
                   0, 0, 0, 1 ];
   var rad = degree * radScaler;
   var sin = Math.sin(rad);
   var cos = Math.cos(rad);
   rMatrix[5]  = cos;
   rMatrix[6]  = -sin;
   rMatrix[9]  = sin;
   rMatrix[10] = cos;
   return rMatrix;
}

// Returns a matrix that will rotate an object by x degrees
function getYRotationMatrix(degree)
{
   var rMatrix = [
                   1, 0, 0, 0,
                   0, 1, 0, 0,
                   0, 0, 1, 0,
                   0, 0, 0, 1 ];
   var rad = degree * radScaler;
   var sin = Math.sin(rad);
   var cos = Math.cos(rad);
   rMatrix[0]  = cos;
   rMatrix[2]  = sin;
   rMatrix[8]  = -sin;
   rMatrix[10] = cos;
   return rMatrix;
}


// Returns a translation matrix given by x, y, z displacements
function getTranslationMatrix(x, y, z)
{
   return [1, 0, 0, x,
           0, 1, 0, y,
           0, 0, 1, z,
           0, 0, 0, 1];
}

// Returns a scale matrix
function getScaleMatrix(x, y, z)
{
   return [x, 0, 0, 0,
           0, y, 0, 0,
           0, 0, z, 0,
           0, 0, 0, 1];
}

// Hmm
lerp = function(A, B, T)
{
   return (B - A) * T + A; 
}

// Lerps a vector
lerpVector = function(v1, v2, t)
{
   var v3 = new Array();
   for (var i = 0; i < v1.length; i++)
   {
      v3[i] = lerp(v1[i], v2[i], t);
   }
   return v3;
}

// Make a vec4 by post-multiplying the matrix by the vector
matrixPostMult = function(m, v)
{
   return [
      m[ 0] * v[0] + m[ 1] * v[1] + m[ 2] * v[2] + m[ 3] * v[3], 
      m[ 4] * v[0] + m[ 5] * v[1] + m[ 6] * v[2] + m[ 7] * v[3],
      m[ 8] * v[0] + m[ 9] * v[1] + m[10] * v[2] + m[11] * v[3],
      m[12] * v[0] + m[13] * v[1] + m[14] * v[2] + m[15] * v[3]
      ];
}

vectorAdd = function(A, B)
{
   return [
      A[0] + B[0], A[1] + B[1], A[2] + B[2], A[3] + B[3]
   ];
}

vectorSubtract = function(A, B)
{
   return [
      A[0] - B[0], A[1] - B[1], A[2] - B[2], A[3] - B[3]
   ];
}

vectorMult = function(A, s)
{
   return [
      A[0] * s, A[1] * s, A[2] * s, A[3] * s
   ];
}

// Note that this one ONLY does a 3D cross product
vectorCross = function(A, B)
{
   return [
      A[1] * B[2] - A[2] * B[1],
      A[2] * B[0] - A[0] * B[2],
      A[0] * B[1] - A[1] * B[0]
      ];
}

vectorDot = function(A, B)
{
   return A[0] * B[0] + A[1] * B[1] + A[2] * B[2] + A[3] * B[3];
}

vectorLength = function(V)
{
   return Math.sqrt(vectorDot(V, V));
}

// Normalize in place and return true if it worked.
// Will fail if length is 0.
vectorNormalize = function(V)
{
   var len = vectorLength(V);
   if (len > 0.000001)
   {
      var iLen = 1/len;
      V[0] *= iLen; V[1] *= iLen; V[2] *= iLen; V[3] *= iLen;
      return true;
   }
   else
   {
      return false;
   }
}

vectorEquals = function(v1, v2)
{
   return ((v1[0] == v2[0]) && 
	   (v1[1] == v2[1]) && 
	   (v1[2] == v2[2]));
}
