// ???
function MatrixTransformShader(positionIdx, transformMatrix)
{
   this.main = function(vertex)
   {
      return multiplyVector(transformMatrix, vertex[positionIdx]) 
   }   
}
