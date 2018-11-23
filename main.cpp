#include "Graph.h"
#include "Dijkstra.h"

namespace stations {

	// U3
	joule::Station::ID Barmbek = 0;
	joule::Station::ID Kellinghusenstrasse = 1;
	joule::Station::ID LuebeckerStrasse = 2;
	joule::Station::ID Feldstrasse = 3;

	// U2
	joule::Station::ID Emilienstrasse = 4;
	joule::Station::ID Schlump = 5;
	joule::Station::ID BerlinerTor = 6;
	joule::Station::ID Billstedt = 7;

	// U1
	joule::Station::ID Lattenkamp = 8;
	joule::Station::ID Klosterstern = 9;
	joule::Station::ID Jungfernstieg = 10;
	joule::Station::ID Farmsen = 11;
}

int main() {

	joule::Graph graph;

	// U3 internal
	graph.addConnection(stations::Barmbek, stations::Kellinghusenstrasse, 7.);
	graph.addConnection(stations::Barmbek, stations::LuebeckerStrasse, 8.);
	graph.addConnection(stations::Kellinghusenstrasse, stations::Feldstrasse, 8.);
	graph.addConnection(stations::Feldstrasse, stations::LuebeckerStrasse, 14.);

	// U3 external
	graph.addConnection(stations::Kellinghusenstrasse, stations::Schlump, 4.);
	graph.addConnection(stations::LuebeckerStrasse, stations::BerlinerTor, 1.);

	// U2 internal
	graph.addConnection(stations::Emilienstrasse, stations::Schlump, 4.);
	graph.addConnection(stations::Schlump, stations::BerlinerTor, 8.);
	graph.addConnection(stations::BerlinerTor, stations::Billstedt, 10.);

	// U1 internal
	graph.addConnection(stations::Lattenkamp, stations::Klosterstern, 9.);
	graph.addConnection(stations::Klosterstern, stations::Jungfernstieg, 6.);
	graph.addConnection(stations::Jungfernstieg, stations::Farmsen, 25.);

	joule::Dijkstra dijkstra{graph};
	auto path{dijkstra.getMinPath(stations::LuebeckerStrasse, stations::Emilienstrasse)};
	auto cost{0.};
	std::cout << "Found " << path.size() << " stations" << std::endl;
	for (int i{path.size()-1}; 0 <= i; --i) {
		if (0 < i) {
			cost += graph.getDuration(path[i], path[i-1]);
		}
		std::cout << "Station: " << path[i] << " duration: " << cost << std::endl;
	}
}

