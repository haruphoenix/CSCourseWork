bin/Arcana: src/system/main.cpp lib/ArcTimer.o lib/ArcWindow.o lib/ArcEngine.o lib/ArcModel.o lib/ArcController.o lib/ArcApp.o lib/ArcMath.o lib/ArcShader.o lib/ArcUtils.o lib/ArcCamera.o lib/ArcShaderProgram.o lib/ArcCanvas.o lib/ArcVertexData.o lib/ArcTerrain.o
	g++ -I /usr/include/ $^ $(pkg-config --cflags --libs sdl2) -o $@ -I include/model -I include/view -I include/controller -I include/system -lSDL2main -lSDL2 -lGL -lGLU -lGLEW 

lib/ArcTimer.o: src/system/ArcTimer.cpp
	g++ -c $^ -o $@ -I include/model -I include/view -I include/controller -I include/system

lib/ArcWindow.o: src/view/ArcWindow.cpp
	g++ -c $^ -o $@ -I include/model -I include/view -I include/controller -I include/system

lib/ArcEngine.o: src/view/ArcEngine.cpp
	g++ -c $^ -o $@ -I include/model -I include/view -I include/controller -I include/system

lib/ArcModel.o: src/model/ArcModel.cpp
	g++ -c $^ -o $@ -I include/model -I include/view -I include/controller -I include/system

lib/ArcController.o: src/controller/ArcController.cpp
	g++ -c $^ -o $@ -I include/model -I include/view -I include/controller -I include/system

lib/ArcApp.o: src/system/ArcApp.cpp
	g++ -c $^ -o $@ -I include/model -I include/view -I include/controller -I include/system

lib/ArcUtils.o: src/view/ArcUtils.cpp
	g++ -c $^ -o $@ -I include/model -I include/view -I include/controller -I include/system

lib/ArcShader.o: src/view/ArcShader.cpp
	g++ -c $^ -o $@ -I include/model -I include/view -I include/controller -I include/system

lib/ArcMath.o: src/view/ArcMath.cpp
	g++ -c $^ -o $@ -I include/model -I include/view -I include/controller -I include/system

lib/ArcCamera.o: src/view/ArcCamera.cpp
	g++ -c $^ -o $@ -I include/model -I include/view -I include/controller -I include/system

lib/ArcShaderProgram.o: src/view/ArcShaderProgram.cpp
	g++ -c $^ -o $@ -I include/model -I include/view -I include/controller -I include/system

lib/ArcCanvas.o: src/view/ArcCanvas.cpp
	g++ -c $^ -o $@ -I include/model -I include/view -I include/controller -I include/system

lib/ArcVertexData.o: src/view/ArcVertexData.cpp
	g++ -c $^ -o $@ -I include/model -I include/view -I include/controller -I include/system

lib/ArcTerrain.o: src/model/ArcTerrain.cpp
	g++ -c $^ -o $@ -I include/model -I include/view -I include/controller -I include/system

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
