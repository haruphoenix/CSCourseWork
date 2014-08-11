// Multiplies two 4x4 matrices together
function multiply4by4(m1, m2)
{
   var m3 = new Array();
   for (var i = 0; i < 16; i++)
   {
      m3[i] = matrixCrossProduct(m1, m2, Math.floor(i * .25), i % 4);
   }
   return m3;
}

// Does matrix multiplication of a matrix and a vector
function multiplyVector(m1, v1)
{
   var v2 = new Array();
   for (var i = 0; i < 4; i++)
   {
      v2[i] = vectorCrossProduct(m1, v1, i);
   }
   return v2;
}

// Computes a cross product of a given row and column
function matrixCrossProduct(m1, m2, r, c)
{
   var sum = 0;
   for (var i = 0; i < 4; i++)
   {
      sum += m1[(4 * r) + i] * m2[(4 * i) + c];
   }
   return sum;
}

// Cross Product for vectors
function vectorCrossProduct(m1, v1, r)
{
   var sum = 0;
   for (var i = 0; i < 4; i++)
   {
      sum += m1[(4 * r) + i] * v1[i];
   }
   return sum;
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

var radScaler = Math.PI / 180;

// Returns a matrix that will rotate an object by x degrees
function getRotationMatrix(degree)
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
