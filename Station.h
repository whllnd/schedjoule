#pragma once

#include <string>
#include <vector>

namespace joule {

struct Route;
struct Station {
	using ID = int;
	using Name = std::string;

	int id;
	std::string name;
	//std::vector<Route::ID> routes;
	std::vector<int> routes;
};

struct Route {
	using ID = int;
	using Name = std::string;

	int id;
	std::string name;
	//std::vector<Station::ID> stations;
	std::vector<int> stations;
};

} // namespace joule
