all:
	gcc -Iinclude/ src/app.c src/camera.c src/main.c src/scene.c src/water.c src/ground.c src/car.c src/house.c src/texture.c src/skybox.c src/utils.c -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lobj -lopengl32 -lm -o Porsche.exe -Wall -Wextra -Wpedantic

linux:
	gcc -Iinclude/ src/app.c src/camera.c src/main.c src/scene.c src/water.c src/texture.c src/utils.c -lobj -lSDL2 -lSDL2_image -lGL -lm -o Porsche -Wall -Wextra -Wpedantic
