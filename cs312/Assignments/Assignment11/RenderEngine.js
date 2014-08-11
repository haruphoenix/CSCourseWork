// Constructor Thingy
function RenderEngine(renderBuffer)
{
   this.renderBuffer = renderBuffer;
}

// Changes Normalized Device Coordinates into Screen Coordinates 
RenderEngine.prototype.ndc2screen = function(coordinate)
{
   coordinate[0] = Math.round(( coordinate[0] + 1) *
			      ((this.renderBuffer.width  - 1) * 0.5));
   coordinate[1] = Math.round((-coordinate[1] + 1) *
			      ((this.renderBuffer.height - 1) * 0.5));
   return coordinate;
}

// Draw Normalized Device Coordinates to the screen
RenderEngine.prototype.drawPoints = function(coordinates, vertexShader, fragmentShader)
{
   for (var i = 0; i < coordinates.length; i++)
   {
      var screenCoordinate = this.ndc2screen(
	                     vertexShader.main(coordinates[i]));
      var color            = fragmentShader.main(
                             vertexShader.getSmoothVars(coordinates[i]));
      this.renderBuffer.setPixel(
           screenCoordinate[0], screenCoordinate[1], color);
   }
}

// Interpolates between points
interpolateCoord = function(pt1, pt2, amt)
{
   var result = new Array();
   for (var i = 0; i < 3; i++)
   {
      result[i] = lerp(pt1[i], pt2[i], amt);
   }
   result[3] = 1;
   return result;
}


// Returns the max distance
getMax = function(start, end)
{
   var W = Math.floor(Math.abs(end[0] - start[0]));
   var H = Math.floor(Math.abs(end[1] - start[1]));
   if (W > H) return W;
   else return H;
}

// Rounds a vector
roundVector = function(vector)
{
   for (var i = 0; i < vector.length; i++) vector[i] = Math.round(vector[i]);
   return vector;
}

// Draws a single line given starting points and end points and colors
RenderEngine.prototype.drawLine = function(start, end, color1, color2)
{
   var max = getMax(start, end); //299
   if (max >= 1)
   {
      var amt = 1 / max;
      for (var i = 0; i < max; i++)
      {
         var coordinate = interpolateCoord( start,    end, i * amt);
         var color      = interpolateCoord(color1, color2, i * amt);
         this.renderBuffer.setPixel(coordinate[0], coordinate[1], color);
      }
   }
   else
   {
      this.renderBuffer.setPixel(start[0], start[1], color1);
      this.renderBuffer.setPixel(end[0], end[1], color2);
   }
}

// Draw a series of lines to the screen
RenderEngine.prototype.drawLines = function(coordinates, indexList,
					    vertexShader, fragShader)
{
   for (var i = 0; i < indexList.length; i += 2)
   {
      var start  = this.ndc2screen(
	           vertexShader.main(coordinates[indexList[i    ]]));
      var end    = this.ndc2screen(
                   vertexShader.main(coordinates[indexList[i + 1]]));
      var startC = vertexShader.getSmoothVars(
                   coordinates[indexList[i]]);
      var endC   = vertexShader.getSmoothVars(
                   coordinates[indexList[i + 1]]);
      this.drawLine(start, end, startC, endC);
   }
}

// Sets the background a solid color
RenderEngine.prototype.setBackground = function(color)
{
   for (var i = 0; i < this.renderBuffer.width; i++)
   {
      for (var j = 0; j < this.renderBuffer.height; j++)
      {
         this.renderBuffer.setPixel(i, j, color);
      }
   }
}

// Draw a gradient to the screen
RenderEngine.prototype.drawGradient = function(lines, color)
{
   var amt1 = Math.round(getMax(lines[0], lines[1]));
   var amt2 = Math.round(getMax(lines[2], lines[3]));
   if (amt1 < amt2) amt1 = amt2;
   for (var i = 0; i < amt1; i++)
   {
      var start      = interpolateCoord(lines[0], lines[1], i / amt1);
      var end        = interpolateCoord(lines[2], lines[3], i / amt1);
      var startColor = interpolateCoord(color[0], color[1], i / amt1);
      var endColor   = interpolateCoord(color[2], color[3], i / amt1);
      //this.renderBuffer.setPixel(start[0], start[1], startColor);
      //this.renderBuffer.setPixel(end[0], end[1], endColor);
      this.drawLine(start, end, startColor, endColor);
   }
}

// Fills a gradient between points
RenderEngine.prototype.drawGradients = function(coordinates, indexList, vertexShader, fragShader)
{
   for (var i = 0; i < indexList.length; i += 4)
   {
      var start1  = this.ndc2screen(vertexShader.main(
                                    coordinates[indexList[i    ]]));
      var end1    = this.ndc2screen(vertexShader.main(
                                    coordinates[indexList[i + 1]]));
      var start2  = this.ndc2screen(vertexShader.main(
                                    coordinates[indexList[i + 2]]));
      var end2    = this.ndc2screen(vertexShader.main(
                                    coordinates[indexList[i + 3]]));
      var lines   = [start1, end1, start2, end2];
      var colorS1 = vertexShader.getSmoothVars(coordinates[indexList[i    ]]);
      var colorE1 = vertexShader.getSmoothVars(coordinates[indexList[i + 1]]);
      var colorS2 = vertexShader.getSmoothVars(coordinates[indexList[i + 2]]);
      var colorE2 = vertexShader.getSmoothVars(coordinates[indexList[i + 3]]);
      var colors  = [colorS1, colorE1, colorS2, colorE2];
      this.drawGradient(lines, colors);
   }
}
