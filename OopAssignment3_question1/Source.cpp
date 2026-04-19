#include "Part2.h"
#include "part3.h"
#include <cstdlib>
using namespace std;

int main() {
	World world(20, 20); //initiating a world grid 20x20

	//adding 2 orgs 
	world.addNewOrg(new FractalSprawler(1, 2, 1, 10));
	world.addNewOrg(new KineticHunter(10, 10,4, 3));

	//running as long as fractals are alive
	for (int i = 0; world.getFractalCount() > 0; i++)
	{
		cout << "// ===== Iteration " << i + 1 << " ===== //";
		cout << endl;
		world.runIteration();
		system("cls");
	}
	return 0;	
}