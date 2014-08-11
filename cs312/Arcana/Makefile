COMPILE = x86_64-w64-mingw32-g++
#COMPILE = i686-w64-mingw32-g++
#COMPILE = g++
IDK_WHAT_THIS_DOES = $(pkg-config --cflags --libs sdl2main sdl2)
INCLUDE_LOCATIONS = -I /usr/include/ -I /usr/local/include -I include/model -I include/view -I include/controller -I include/system
LINKER_LOCATIONS = -L /usr/local/lib
LINKER_FLAGS = -lSDL2main -lSDL2 -lGL -lGLU -lGLEW
ARCANA = bin/Arcana
TIMER = lib/ArcTimer.o
WINDOW = lib/ArcWindow.o
ENGINE = lib/ArcEngine.o
MODEL = lib/ArcModel.o
CONTROLLER = lib/ArcController.o
APP = lib/ArcApp.o
MATH = lib/ArcMath.o
SHADER = lib/ArcShader.o
UTILS = lib/ArcUtils.o
CAMERA = lib/ArcCamera.o
SHADER_PROGRAM = lib/ArcShaderProgram.o
CANVAS = lib/ArcCanvas.o
VERTEX_DATA = lib/ArcVertexData.o
TERRAIN = lib/ArcTerrain.o

$(ARCANA): src/system/main.cpp $(TIMER) $(WINDOW) $(ENGINE) $(MODEL) $(CONTROLLER) $(APP) $(MATH) $(SHADER) $(UTILS) $(CAMERA) $(SHADER_PROGRAM) $(CANVAS) $(VERTEX_DATA) $(TERRAIN)
	$(COMPILE) $(INCLUDE_LOCATIONS) $^ $(IDK_WHAT_THIS_DOES) -o $@ $(LINKER_LOCATIONS) $(LINKER_FLAGS)

$(TIMER): src/system/ArcTimer.cpp
	$(COMPILE) -c $^ -o $@ $(INCLUDE_LOCATIONS)

$(WINDOW): src/view/ArcWindow.cpp
	$(COMPILE) -c $^ -o $@ $(INCLUDE_LOCATIONS)

$(ENGINE): src/view/ArcEngine.cpp
	$(COMPILE) -c $^ -o $@ $(INCLUDE_LOCATIONS)

$(MODEL): src/model/ArcModel.cpp
	$(COMPILE) -c $^ -o $@ $(INCLUDE_LOCATIONS)

$(CONTROLLER): src/controller/ArcController.cpp
	$(COMPILE) -c $^ -o $@ $(INCLUDE_LOCATIONS)

$(APP): src/system/ArcApp.cpp
	$(COMPILE) -c $^ -o $@ $(INCLUDE_LOCATIONS)

$(UTILS): src/view/ArcUtils.cpp
	$(COMPILE) -c $^ -o $@ $(INCLUDE_LOCATIONS)

$(SHADER): src/view/ArcShader.cpp
	$(COMPILE) -c $^ -o $@ $(INCLUDE_LOCATIONS)

$(MATH): src/view/ArcMath.cpp
	$(COMPILE) -c $^ -o $@ $(INCLUDE_LOCATIONS)

$(CAMERA): src/view/ArcCamera.cpp
	$(COMPILE) -c $^ -o $@ $(INCLUDE_LOCATIONS)

$(SHADER_PROGRAM): src/view/ArcShaderProgram.cpp
	$(COMPILE) -c $^ -o $@ $(INCLUDE_LOCATIONS)

$(CANVAS): src/view/ArcCanvas.cpp
	$(COMPILE) -c $^ -o $@ $(INCLUDE_LOCATIONS)

$(VERTEX_DATA): src/view/ArcVertexData.cpp
	$(COMPILE) -c $^ -o $@ $(INCLUDE_LOCATIONS)

$(TERRAIN): src/model/ArcTerrain.cpp
	$(COMPILE) -c $^ -o $@ $(INCLUDE_LOCATIONS)

clean:
	touch bin/Arcana lib/trash.o
	rm bin/Arcana lib/*.o
	clear

magic:
	make clean
	make

magical:
	make magic arcane

arcane:
	clear
	bin/Arcana
	clear

work:
	clear
	touch trash
	rm trash
	make
	clear
	bin/Arcana >> trash
	clear
	emacs trash
	clear
