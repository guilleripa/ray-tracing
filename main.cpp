#include <iostream>
#include "../tinyxml2.h"
#include "OpenGL-basico/Whitted.h"

using namespace std;

int main(int argc, char *argv[]) {

	try {
		Scene scene = Scene().loadScene();
		Whitted().run(scene);
	}
	catch (int param) {
		if (param == 6) {
			cout << "Error al cargar escena";
		}
		return 1;
	}

	return 0;
}
