#pragma once

#include "Graph.h"

#include <iostream>
#include <queue>
#include <vector>

#include <boost/heap/binomial_heap.hpp>

namespace joule {

class Dijkstra {
public:

	struct Cost {
		Cost(Station::ID id, double d) : station{id}, duration{d} {}
		Station::ID station{-1};
		double duration{0.};
		bool operator<(Cost const& c) const { return duration > c.duration; } // Inverse to conform with min heap
	};

	Dijkstra(Graph const& graph) : mGraph(graph) {}

	std::vector<Station::ID> getMinPath(Station::ID const start, Station::ID const end) const {

		// Get some periphery going
		MinHeap queue;
		std::map<Station::ID, MinHeap::handle_type> handles;
		std::map<Station::ID, Station::ID> predecessors;

		// Initialize nodes
		for (auto const& [id, node] : mGraph.getNodes()) {
			handles[id] = queue.emplace(id, std::numeric_limits<double>::infinity());
			predecessors[id] = -1;
		}
		auto& startHandle{handles[start]};
		(*startHandle).duration = 0.;
		queue.update(startHandle);

		// For each node in queue, process its neighbors and keep track of duration
		for (;!queue.empty();) {
			auto node{queue.top()};
			queue.pop();
			handles.erase(node.station);

			// If we reached destination, return predecessor path
			if (end == node.station) {
				std::vector<Station::ID> path;
				for (auto station{end}; -1 != predecessors[station]; station = predecessors[station]) {
					path.push_back(station);
				}
				path.push_back(start);
				return path;
			}

			for (auto const successor : mGraph.getConnections(node.station)) {
				if (auto succHandle{handles.find(successor)}; handles.end() != succHandle) {
					if (auto dur{node.duration + mGraph.getDuration(node.station, successor)};
					    dur < (*(succHandle->second)).duration
					) {
						(*(succHandle->second)).duration = dur;
						predecessors[successor] = node.station;
					}
				}
			}
		}

		return {};
	}

private:

	using MinHeap = boost::heap::binomial_heap<Cost>;
	Graph const& mGraph;
};

} // namespace joule
