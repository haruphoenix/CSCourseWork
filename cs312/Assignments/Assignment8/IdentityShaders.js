// Don't know what this class will do
function IdentityVertexShader(positionIndex)
{
   this.main = function(vertex)
   {
      return vertex[positionIndex];
   }
}


// Don't know what this class will do
function BasicColorFragmentShader(colorIndex)
{
   this.main = function(vertex)
   {
      return vertex[colorIndex];
   }
}

