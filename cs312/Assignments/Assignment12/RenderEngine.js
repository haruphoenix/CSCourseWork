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

// Direction to show
var clockwiseWinding = true;

// Draw Triangles to the screen.
RenderEngine.prototype.drawTriangles = function(verts, indexListTris,
                                                winding,
                                                vertexShader, fragmentShader)
{
   for (var i = 0; i < indexListTris.length; i += 3)
   {
      var isCounter = getDirection(vertexShader.main(verts[indexListTris[i    ]]),
		      vertexShader.main(verts[indexListTris[i + 1]]),
		      vertexShader.main(verts[indexListTris[i + 2]]));
      if ( ((!isCounter) && (winding)) || ((isCounter) && (!winding)))
      {
         var indexList = [indexListTris[i    ], indexListTris[i + 1],
                          indexListTris[i + 1], indexListTris[i + 2],
                          indexListTris[i + 2], indexListTris[i    ]];
         this.drawLines(verts, indexList, vertexShader, fragmentShader);
      }
   }
}

// Draw Triangles to the screen.
RenderEngine.prototype.drawTrianglesa = function(verts, indexListTris,
                                                winding,
                                                vertexShader, fragmentShader)
{
   vertices = new Array();
   for (var i = 0; i < verts.length; i++)
   {
      vertices[i] = vertexShader.main(verts[i]);
   }

   for (var i = 0; i < indexListTris.length; i += 3)
   {
      var points = new Array();
      for (var j = 0; j < 3; j++)
      {
         points[j] = vertices[indexListTris[i + j]];
      }
      var isClockwise = getDirection(points[0], points[1], points[2]);
      if ( ((!isClockwise) && (winding)) || ((isClockwise) && (!winding)))
      {
         var colors = new Array();
         for (var j = 0; j < 3; j++)
         {
            points[j] = this.ndc2screen(points[j]);
            colors[j] = vertexShader.getSmoothVars(verts[indexListTris[i + j]]);
         }
         for (var j = 0; j < 3; j++)
         {
            console.log("line" + i + " " + j);
            this.drawLine(points[j], points[(j + 1) % 3], colors[j], colors[(j + 1) % 3]);
         }
      }
   }
}
