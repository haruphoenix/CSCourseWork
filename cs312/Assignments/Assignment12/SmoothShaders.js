

function MatrixSmoothVertShader(positionIdx, colorIdx, projMatrix)
{
   this.main = function(vertex)
   {
      return multiplyVector(projMatrix, vertex[positionIdx]);
   }

   this.getSmoothVars = function(vertex)
   {
      return vertex[colorIdx];
   }
}

function SmoothColorFragShader()
{
   this.main = function(varyingVars)
   {
      return varyingVars;
   }
}
