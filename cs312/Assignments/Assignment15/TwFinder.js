function TwFinder(w1, w2)
{
   if (w1 != w2)
   {
      var iW1 = 1 / w1;
      var iW2 = 1 / w2;
      var iDW = 1 / (w2 - w1);
      
      this.findT = function(t)
         {
            var w = 1 / lerp(iW1, iW2, t);
            // Return an array with the new t AND w value
            return [(w - w1) * iDW, w];
         }
   }
   else
   {
      this.findT = function(t)
         {
            return [t, w1];
         }
   }
}
