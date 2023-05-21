all:
	gcc -Iinclude/ src/app.c src/camera.c src/collision.c src/ghost.c src/kid.c src/main.c src/ray.c src/scene.c src/texture.c src/utils.c -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lobj -lopengl32 -lm -o game.exe -Wall -Wextra -Wpedantic

linux:
	gcc -Iinclude/ src/app.c src/camera.c src/collision.c src/ghost.c src/kid.c src/main.c src/ray.c src/scene.c src/texture.c src/utils.c -lobj -lSDL2 -lSDL2_image -lGL -lm -o game -Wall -Wextra -Wpedantic
