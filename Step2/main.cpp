#include <iostream>
#include <fstream>
#include <cstdlib>
#include <time.h>
#include <vector>
using namespace std;
#include "Random.h"
#include "Read.h"
#include "Monomer.h"
#include "Polymer.h"
#include "Box.h"

int main(int argc, char *const argv[])
{
	const int total_number_of_steps = 50000;
	const int number_of_beads = 100;
	vector<Monomer *> beads(number_of_beads);
	vector<double> line;
	Read read;
	read.setFileName("/Users/io/Project/Polymer_Monte_Carlo/Step2/start.txt");
	read.openFile();
	for (int i = 0; i < number_of_beads; i++)
	{
		beads[i] = new Monomer;
		line = read.getLine();
		beads[i]->SetX(line[0]);
		beads[i]->SetY(line[1]);
		beads[i]->SetZ(line[2]);
	}
	read.closeFile();
	const int number_of_polymers = 10;
	const int number_of_beads_in_polymer = 10;
	vector<Polymer *> polymers(number_of_polymers);

	for (int i = 0; i < number_of_polymers; i++)
	{
		polymers[i] = new Polymer;
		polymers[i]->set_Cutoff(2.0);
		for (int j = 0; j < number_of_beads_in_polymer; j++)
		{
			polymers[i]->addMonomer(beads[j + i * number_of_beads_in_polymer]);
		}
	}

	double box_x = 20.0;
	double box_y = 20.0;
	double box_z = 20.0;
	Box *box = new Box(box_x, box_y, box_z);
	box->addPolymers(polymers);
	// box->setBoxMaxStepSize(0.5);

	FILE *_stream;
	_stream = fopen("/Users/io/Project/Polymer_Monte_Carlo/Step2/finish.csv", "w");
	fprintf(_stream, "timestep,chain,monomer,x,y,z\n");
	for (int i = 0; i < total_number_of_steps; i++)
	{
		box->move();
		// fprintf(_stream, "%d\n", i);
		// fprintf(_stream, "%lf\t%lf\t%lf\n", box->getX(), box->getY(), box->getZ());
		for (int j = 0; j < number_of_polymers; j++)
		{
			for (int k = 0; k < number_of_beads_in_polymer; k++)
			{
				Monomer *temp;
				temp = polymers[j]->getMonomer(k);
				float x = temp->GetX();
				float y = temp->GetY();
				float z = temp->GetZ();
				if (i % 1 == 0)
				{
					fprintf(_stream, "%d,%d,%d,%lf,%lf,%lf\n", i, j, k, x, y, z);
					fprintf(_stream, "\n");
				}
			}
		}
	}
	fclose(_stream);
	cout << "finish" << endl;
	return 0;
}
