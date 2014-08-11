// Constructor Thingy
function RenderEngine(renderBuffer)
{
   this.renderBuffer = renderBuffer;
}

// Changes Normalized Device Coordinates into Screen Coordinates 
RenderEngine.prototype.ndc2screen = function(coordinate)
{
   coordinate[0] = ( coordinate[0] + 1) * ((this.renderBuffer.width  - 1) * 0.5);
   coordinate[1] = (-coordinate[1] + 1) * ((this.renderBuffer.height - 1) * 0.5);
   return coordinate;
}



// Draw Normalized Device Coordinates to the screen
RenderEngine.prototype.drawPoints = function(coordinates, vertexShader, colorShader)
{
   for (var i = 0; i < coordinates.length; i++)
   {
      var screenCoordinate = this.ndc2screen(vertexShader(coordinates[i]));
      var color            = colorShader(coordinates[i]);
      this.renderBuffer.setPixel(screenCoordinate[0], screenCoordinate[1], color);
   }
}
