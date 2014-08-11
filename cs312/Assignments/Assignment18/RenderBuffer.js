function ScanLine(imageData, y, width)
{
   this.offset = y * imageData.width;
   this.imageData = imageData;
   this.width = width;
}
 
ScanLine.prototype.setPixel = function(x, color)
{
   // TODO: Remove when clipping is solid!
   if ((x < 0) || (x >= this.width))
   {
      alert("OUT of BOUNDS! x= " + x + ", y= " + y);
      return;
   }
   var offset = (this.offset + x) * 4;
   this.imageData.data[offset + 0] = color[0] * 255;
   this.imageData.data[offset + 1] = color[1] * 255;
   this.imageData.data[offset + 2] = color[2] * 255;
   this.imageData.data[offset + 3] = color[3] * 255;
}

RenderBuffer.prototype.getScanLine = function(y)
{
   // TODO: Remove when clipping is solid!
   if ((y < 0) || (y >= this.height))
   {
      alert("OUT of BOUNDS! x= " + x + ", y= " + y);
      return;
   }
   return new ScanLine(this.imageData, y, this.width);
}

function RenderBuffer(elementID)
{
   var canvas = document.getElementById(elementID);
   this.context = canvas.getContext("2d");
   this.width = canvas.width;
   this.height = canvas.height;
   this.imageData = this.context.createImageData(canvas.width, canvas.height);
   this.depthBuffer = new Array(this.width * this.height);
   this.resetBuffer();
}

RenderBuffer.prototype.resetBuffer = function()
{
   for (var i = 0; i < this.depthBuffer.length; i++)
   {
      this.depthBuffer[i] = 1000000;
   }
}

RenderBuffer.prototype.flush = function()
{
   this.context.putImageData(this.imageData, 0, 0);
   this.resetBuffer();
}

// Color must be a vec4: [r, g, b, a]
RenderBuffer.prototype.setPixel = function(x, y, z, color)
{
   // TODO: Remove when clipping is solid!
   if ((x < 0) || (x >= this.width) ||
       (y < 0) || (y >= this.height))
   {
      alert("OUT of BOUNDS! x= " + x + ", y= " + y);
      return;
   }
   if (z > this.depthBuffer[y * this.width + x]) return;
   this.depthBuffer[y * this.width + x] = z;
   var offset = (y * this.width + x) * 4;
   this.imageData.data[offset + 0] = color[0] * 255;
   this.imageData.data[offset + 1] = color[1] * 255;
   this.imageData.data[offset + 2] = color[2] * 255;
   this.imageData.data[offset + 3] = color[3] * 255;
}
