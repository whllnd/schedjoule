#include "Station.h"
#include "Graph.h"
#include "Dijkstra.h"

namespace stations {

	// U3
	joule::Station Barmbek{0, "Barmbek", {}};
	joule::Station Kellinghusenstrasse{1, "Kellinghusenstraße", {}};
	joule::Station LuebeckerStrasse{2, "Lübecker Straße", {}};
	joule::Station Feldstrasse{3, "Feldstraße", {}};

	// U2
	joule::Station Emilienstrasse{4, "Emilienstraße", {}};
	joule::Station Schlump{5, "Schlump", {}};
	joule::Station BerlinerTor{6, "Berliner Tor", {}};
	joule::Station Billstedt{7, "Billstedt", {}};

	// U1
	joule::Station Lattenkamp{8, "Lattenkamp", {}};
	joule::Station Klosterstern{9, "Klosterstern", {}};
	joule::Station Jungfernstieg{10, "Jungfernstieg", {}};
	joule::Station Farmsen{11, "Farmsen", {}};

	std::map<joule::Station::ID, joule::Station*> stations{
		{Barmbek.id, &Barmbek},
		{Kellinghusenstrasse.id, &Kellinghusenstrasse},
		{LuebeckerStrasse.id, &LuebeckerStrasse},
		{Feldstrasse.id, &Feldstrasse},
		{Emilienstrasse.id, &Emilienstrasse},
		{Schlump.id, &Schlump},
		{BerlinerTor.id, &BerlinerTor},
		{Billstedt.id, &Billstedt},
		{Lattenkamp.id, &Lattenkamp},
		{Klosterstern.id, &Klosterstern},
		{Jungfernstieg.id, &Jungfernstieg},
		{Farmsen.id, &Farmsen}
	};
}

namespace routes {

	joule::Route U3{3, "U3", {stations::Barmbek.id,
	                          stations::Kellinghusenstrasse.id,
	                          stations::LuebeckerStrasse.id,
	                          stations::Feldstrasse.id}};

	joule::Route U2{2, "U2", {stations::Emilienstrasse.id,
	                          stations::Schlump.id,
	                          stations::BerlinerTor.id,
	                          stations::Billstedt.id}};

	joule::Route U1{1, "U1", {stations::Lattenkamp.id,
	                          stations::Klosterstern.id,
	                          stations::Jungfernstieg.id,
	                          stations::Farmsen.id}};
}

int main() {

	// Set routes
	stations::Barmbek.routes = {routes::U3.id};
	stations::Kellinghusenstrasse.routes = {routes::U3.id, routes::U2.id};
	stations::LuebeckerStrasse.routes = {routes::U3.id, routes::U2.id};
	stations::Feldstrasse.routes = {routes::U3.id};
	stations::Emilienstrasse.routes = {routes::U2.id};
	stations::Schlump.routes = {routes::U2.id, routes::U3.id};
	stations::BerlinerTor.routes = {routes::U2.id, routes::U3.id};
	stations::Billstedt.routes = {routes::U2.id};
	stations::Lattenkamp.routes = {routes::U1.id};
	stations::Klosterstern.routes = {routes::U1.id};
	stations::Jungfernstieg.routes = {routes::U1.id};
	stations::Farmsen.routes = {routes::U1.id};

	joule::Graph graph;

	// U3 internal
	graph.addConnection(stations::Barmbek.id, stations::Kellinghusenstrasse.id, 7.);
	graph.addConnection(stations::Barmbek.id, stations::LuebeckerStrasse.id, 8.);
	graph.addConnection(stations::Kellinghusenstrasse.id, stations::Feldstrasse.id, 8.);
	graph.addConnection(stations::Feldstrasse.id, stations::LuebeckerStrasse.id, 14.);

	// U3 external
	graph.addConnection(stations::Kellinghusenstrasse.id, stations::Schlump.id, 4.);
	graph.addConnection(stations::LuebeckerStrasse.id, stations::BerlinerTor.id, 1.);

	// U2 internal
	graph.addConnection(stations::Emilienstrasse.id, stations::Schlump.id, 4.);
	graph.addConnection(stations::Schlump.id, stations::BerlinerTor.id, 8.);
	graph.addConnection(stations::BerlinerTor.id, stations::Billstedt.id, 10.);

	// U1 internal
	graph.addConnection(stations::Lattenkamp.id, stations::Klosterstern.id, 9.);
	graph.addConnection(stations::Klosterstern.id, stations::Jungfernstieg.id, 6.);
	graph.addConnection(stations::Jungfernstieg.id, stations::Farmsen.id, 25.);

	joule::Dijkstra dijkstra{graph};
	auto path{dijkstra.getMinPath(stations::LuebeckerStrasse, stations::Emilienstrasse)};
	auto cost{0.};
	std::cout << path.size() << " stations:" << std::endl;
	for (int i{int(path.size()-1)}; 0 <= i; --i) {
		if (0 < i) {
			cost += graph.getDuration(path[i], path[i-1]);
		}
		std::cout << (int(path.size()-1) == i ? "" : " -> ") << stations::stations[path[i]]->name;
	}
	std::cout << "\nDuration: " << cost << "min" << std::endl;
}

