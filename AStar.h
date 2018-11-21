#pragma once

#include <Graph.h>

#include <queue>

namespace joule {

class AStar {
public:

	struct Duration {
		Station::ID id;
		double duration;
		bool operator<(Duration const& d) const { return duration < d.duration; }
	};

	AStar(Graph const& graph) : mGraph(graph) {}

	std::vector<Station::ID> getMinPath(Graph::Connection const& conn) {
		std::vector<Station::ID> path;
		std::priority_queue<Duration> openList;
		openList.emplace(conn.start, 0.);
		for (; !openList.empty();) {
			auto node(openList.top());
			openList.pop();

			if (conn.end == node.id) {
				return path;
			}

			path.push_back(node.id);
			expand(node);
		}
		return {};
	}

private:

	void expand(Duration const& node,
	            std::priority_queue<Duration>& openList,
		        std::set<Station::ID>& closedList,
		        std::map<Station::ID, double>& const durations) const
	{
		for (auto const successor : mGraph.getSuccessors(node.id)) {
			if (0 < closedList.count(successor)) {
				continue;
			}

			auto duration{durations[node.id] + mGraph.getDuration(node.id, successor)};
			if (openList.duration >= durations[successor]) {
				continue;
			}


		foreach successor of currentNode
			// wenn der Nachfolgeknoten bereits auf der Closed List ist – tue nichts
			if closedlist.contains(successor) then
				continue
			// g-Wert für den neuen Weg berechnen: g-Wert des Vorgängers plus
			// die Kosten der gerade benutzten Kante
			tentative_g = g(currentNode) + c(currentNode, successor)
			// wenn der Nachfolgeknoten bereits auf der Open List ist,
			// aber der neue Weg nicht besser ist als der alte – tue nichts
			if openlist.contains(successor) and tentative_g >= g(successor) then
				continue
			// Vorgängerzeiger setzen und g Wert merken
			successor.predecessor := currentNode
			g(successor) = tentative_g
			// f-Wert des Knotens in der Open List aktualisieren
			// bzw. Knoten mit f-Wert in die Open List einfügen
			f := tentative_g + h(successor)
			if openlist.contains(successor) then
				openlist.decreaseKey(successor, f)
			else
				openlist.enqueue(successor, f)
		end

	Graph const& mGraph;
};

} // namespace joule
