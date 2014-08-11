
function RenderBuffer(canvasName)
{
   var canvas = document.getElementById(canvasName);
   var ctx = canvas.getContext("2d");
   var imageData = ctx.createImageData(canvas.width, canvas.height);

   this.width  = imageData.width;
   this.height = imageData.height;
   this.data   = imageData.data;

   this.flush = function()
   {
       ctx.putImageData(imageData, 0, 0);
   }
}



