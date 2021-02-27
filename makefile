all:
	mkdir -p build
	gcc src/fixed_point.c src/vec3.c src/main.c -o build/raytracing

temps:
	mkdir -p build
	gcc src/fixed_point.c src/vec3.c src/main.c -save-temps=obj -o build/raytracing

clean:
	rm -rf build
