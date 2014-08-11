
// Returns orthographic projection for given values.
OrthoGraphicProjection = function(left, right, top, bottom, near, far)
{
   var A = 2 / (right - left);
   var B = -(right + left)/(right - left);
   var C = 2 / (top - bottom);
   var D = -(top + bottom)/(top - bottom);
   var E = -2 / (far - near);
   var F = (far + near)/(far - near);
   return [A, 0, 0, B,
           0, C, 0, D,
           0, 0, E, F,
           0, 0, 0, 1];
}

// Returns an orthographic projection for keeping the aspect ratio
OrthoGraphicProjectionWithAspectRatio = function(aspectRatio)
{
   var T = 1;
   var B = -1;
   var L = -1;
   var R = 1;
   var N = 1;
   var F = -1;
   if (aspectRatio < 1)
   {
      T /= aspectRatio;
      B /= aspectRatio;
   }
   else if (aspectRatio > 1)
   {
      L *= aspectRatio;
      R *= aspectRatio;
   }
   return OrthoGraphicProjection(L, R, T, B, N, F);
}