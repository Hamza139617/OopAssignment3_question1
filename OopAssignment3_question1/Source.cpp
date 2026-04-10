#include "Part2.h"
#include "part3.h"

using namespace std;

int main() {
	World world(20, 20); //initiating a world grid 20x20

	//adding 2 orgs 
	world.addNewOrg(new FractalSprawler(2, 2, 3, 3));
	world.addNewOrg(new KineticHunter(10, 10, 3, 3));

	//running as long as fractals are alive
	for (int i = 0; world.getFractalCount() > 0; i++)
	{
		cout << "// ===== Iteration " << i + 1 << " ===== //";
		cout << endl;
		world.runIteration();
	}
	return 0;	
}