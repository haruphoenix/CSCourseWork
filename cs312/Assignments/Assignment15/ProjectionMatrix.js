OrthoGraphicProjection = function(left, right, top, bottom, near, far)
{
   return [
      2/(right-left), 0,              0,            -((right+left)/(right-left)),
      0,              2/(top-bottom), 0,            -((top+bottom)/(top-bottom)),
      0,              0,              2/(far-near), -((far+near)/(far-near)),
      0,              0,              0,            1
   ];
}

OrthoGraphicProjectionWithAspectRatio = function(aspectRatio)
{
   var left = -1;
   var right = +1;
   var top = +1;
   var bottom = -1;
   var near = -1;
   var far = +1;
   if (aspectRatio > 1.0)
   {
      left *= aspectRatio;
      right *= aspectRatio;
   }
   else
   {
      top /= aspectRatio;
      bottom /= aspectRatio;
   }
   
   return OrthoGraphicProjection(left, right, top, bottom, near, far);
}

// This should work. :/
PerspectiveProjection = function(L, R, B, T, N, F)
{
    var X1 =      (2 * N) / (R - L);
    var X2 =      (R + L) / (R - L);
    var Y1 =      (2 * N) / (T - B);
    var Y2 =      (T + B) / (T - B);
    var Z1 =     -(F + N) / (F - N);
    var Z2 = -(2 * F * N) / (F - N);
    return [X1,  0, X2,  0,
             0, Y1, Y2,  0,
             0,  0, Z1, Z2,
             0,  0, -1,  0];
}

// This code was taken from songho.ca/opengl/gl_transform.html
// This creates a symmetric frustum.
// It converts to 6 params (l, r, b, t, n, f) for glFrustum()
// from given 4 params (fovY, aspect, near, far)
PerspectiveProjectionWithAspectRatio = function(aspectRatio, fovY, front, back)
{
    var DEG2RAD = Math.PI / 180;

    var tangent = Math.tan(fovY/2 * DEG2RAD); // tangent of half fovY
    var height  = front * tangent;            // half height of near plane
    var width   = height * aspectRatio;       // half width of near plane
    
    // params: left, right, bottom, top, near, far
    return PerspectiveProjection(-width, width, -height, height, front, back);
}
