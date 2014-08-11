
var MAX = 255;

// Returns a color object given red, green, blue, and alpha values
function color(r, g, b, a)
{
    var C = new Object();
    C.r = r; C.g = g; C.b = b; C.a = a;
    return C;
}

// Set a pixel in the imgData object and the x y coordinate to a certain color
function setPixel(imgData, x, y, C)
{
    var offset = ((y * imgData.width * 4) + (x * 4));
    imgData.data[offset    ] = MAX * C.r;
    imgData.data[offset + 1] = MAX * C.g;
    imgData.data[offset + 2] = MAX * C.b;
    imgData.data[offset + 3] = MAX * C.a;
}

// Find a color inbetween the two colors given as a ratio from the percent
function colorLerp(color1, color2, percent)
{
    var antiPercent = 1 - percent;
    var r = (color1.r * antiPercent) + (color2.r * percent);
    var g = (color1.g * antiPercent) + (color2.g * percent);
    var b = (color1.b * antiPercent) + (color2.b * percent);
    return color(r, g, b, 1);
}

// Draw a single column as a gradient from one color to another
function drawColumn(imgData, x, startColor, endColor, scaler)
{
    for (var y = 0; y < imgData.height; y++)
    {
	setPixel(imgData, x, y, colorLerp(startColor, endColor, y * scaler));
    }
}

// Draw a single row as a gradient from one color to another
function drawRow(imgData, y, startColor, endColor, scaler)
{
    for (var x = 0; x < imgData.width; x++)
    {
	setPixel(imgData, x, y, colorLerp(startColor, endColor, y * scaler));
    }
}

// Draw a gradient given the imgData object and four colors
function drawGradient(imgData, upperLeft, upperRight, lowerLeft, lowerRight)
{
    var widthScaler  = 1 / imgData.width;
    var heightScaler = 1 / imgData.height;
    for (var x = 0; x < imgData.width; x++)
    {
	var wPercent = x * widthScaler;
	var startColor = colorLerp(upperLeft, upperRight, wPercent)
	var endColor   = colorLerp(lowerLeft, lowerRight, wPercent);
	drawColumn(imgData, x, startColor, endColor, heightScaler);
    }
}