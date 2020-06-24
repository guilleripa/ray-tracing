#include <iostream>
#include "../tinyxml2.h"
#include "OpenGL-basico/Whitted.h"
#include <iostream>
#include <chrono>

using namespace std;

int main(int argc, char *argv[]) {

	try {
		auto start = chrono::system_clock::now();
		Scene scene = Scene().loadScene();
		Whitted().run(scene);
		auto end = chrono::system_clock::now();
		chrono::duration<double> elapsed_seconds = end - start;
		cout << "elapsed time: " << elapsed_seconds.count() << "s\n";
	}
	catch (int param) {
		if (param == 6) {
			cout << "Error al cargar escena";
		}
		return 1;
	}

	return 0;
}
