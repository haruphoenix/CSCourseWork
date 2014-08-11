// Constructor Thingy
function RenderEngine(renderBuffer)
{
   this.renderBuffer = renderBuffer;
}

// Changes Normalized Device Coordinates into Screen Coordinates 
RenderEngine.prototype.ndc2screen = function(coordinates)
{
   var xRatio = (this.renderBuffer.width  - 1) / 2;
   var yRatio = (this.renderBuffer.height - 1) / 2;
   for (var i = 0; i < coordinates.length; i++)
   {
      coordinates[i] = new Array((coordinates[i].getPosition()[0] + 1)  * xRatio,
			         (-coordinates[i].getPosition()[1] + 1) * yRatio,
			          coordinates[i].getColor());
   }

   return coordinates;
}

// Draw Normalized Device Coordinates to the screen
RenderEngine.prototype.drawPoints = function(coordinates)
{
   coordinates = this.ndc2screen(points);
   for (var i = 0; i < coordinates.length; i++)
   {
      this.renderBuffer.setPixel(coordinates[i][0], coordinates[i][1], coordinates[i][2]);
   }
}

