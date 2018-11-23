#pragma once

#include "Station.h"

#include <iostream>
#include <set>
#include <map>

namespace joule {

class Graph {
public:

	struct Connection {
		Station::ID start;
		Station::ID end;
		bool operator<(Connection const& rhs) const {
			return start < rhs.start or (start == rhs.start and end < rhs.end);
		}
	};

	struct Node {
		Station::ID id;
		//std::set<Station::ID> predecessors;
		//std::set<Station::ID> successors;
		std::set<Station::ID> connections;
	};

	Graph() {}

	// Returns 0 if connection non-existent
	double getDuration(Station::ID from, Station::ID to) const {
		if (from > to) {
			std::swap(from, to);
		}
		if (auto conn{mDuration.find({from, to})}; mDuration.end() != conn) {
			return conn->second;
		}
		std::cout << "Unknown connection: " << from << " -> " << to << std::endl;
		throw std::logic_error("Unknown connection");
	}

	void addConnection(Station::ID from, Station::ID to, double const duration) {
		if (from == to) {
			std::cout << "Same IDs. Doing nothing." << std::endl;
			return;
		}

		//if (auto nodeFrom{mNodes.find(from)}; mNodes.end() != nodeFrom) {
		//	nodeFrom->second.successors.insert(to);
		//} else {
		//	mNodes[from] = {from, {}, {to}};
		//}

		//if (auto nodeTo{mNodes.find(to)}; mNodes.end() != nodeTo) {
		//	nodeTo->second.predecessors.insert(from);
		//} else {
		//	mNodes[to] = {to, {from}, {}};
		//}

		if (auto nodeFrom{mNodes.find(from)}; mNodes.end() != nodeFrom) {
			nodeFrom->second.connections.insert(to);
		} else {
			mNodes[from] = {from, {to}};
		}

		if (auto nodeTo{mNodes.find(to)}; mNodes.end() != nodeTo) {
			nodeTo->second.connections.insert(from);
		} else {
			mNodes[to] = {to, {from}};
		}

		if (from > to) {
			std::swap(from, to);
		}
		mDuration[{from, to}] = duration;
	}

	bool exists(Station::ID from, Station::ID to) const {
		return 0 < getDuration(from, to);
	}

	std::set<Station::ID> const& getConnections(Station::ID const id) const {
		if (auto node{mNodes.find(id)}; mNodes.end() != node) {
			return node->second.connections;
		}
		throw std::logic_error("jo!");
	}

	//std::set<Station::ID> const& getSuccessors(Station::ID id) const {
	//	if (auto node{mNodes.find(id)}; mNodes.end() != node) {
	//		return node->second.successors;
	//	}
	//	throw std::logic_error("Dude, no node.");
	//}

	//std::set<Station::ID> const& getPredecessors(Station::ID id) const {
	//	if (auto node{mNodes.find(id)}; mNodes.end() != node) {
	//		return node->second.predecessors;
	//	}
	//	throw std::logic_error("Dude, seriously. No node.");
	//}

	std::map<Station::ID, Node> const& getNodes() const { return mNodes; }

private:
	std::map<Connection, double> mDuration;
	std::map<Station::ID, Node> mNodes;
};

}
