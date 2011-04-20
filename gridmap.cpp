#include "coord.h"
#include "grid.h"
#include "gridmap.h"

#include <queue>


// struct BFSNode
// Data fields:
//     Coord coord: coordinate of this node
//     unsigned dist: distance from the source node to this node
// Used in GridMap::updateRoute()
struct BFSNode {
    BFSNode(Coord coord, unsigned dist)
        :coord(coord),
         dist(dist) {}
    BFSNode() {}
    bool operator<(const BFSNode &rhs) const {
        return dist < rhs.dist;
    }
    Coord coord;
    unsigned dist;
};


// GridMap constructor 
GridMap::GridMap(unsigned width, unsigned height)
    :_width(width),
     _height(height) {
    // construct a two dimensional array of grids
    _grids = new Grid*[height];
    _visited = new bool*[height];
    for (size_t i = 0; i < height; ++i) {
        _grids[i] = new Grid[width];
        _visited[i] = new bool[width];
    }
}

// Destructor
GridMap::~GridMap() {
    for (size_t i = 0; i < _height; ++i) {
        delete _grids[i];
        delete _visited[i];
    }
    delete _grids;
    delete _visited;
}

// Set the target coordinate of the map
void GridMap::setTarget(unsigned x, unsigned y) {
    _target = Coord(x, y);
}

// Update the routes, this method is called each time
// a new tower is built or a present tower is destroyed.
//
// This method uses a variant of Breadth-First Search to
// calculate the routes.
//
// The Creeps can go horizontally, vertically or diagonally.
// A diagonal direction is valid only when the the diagonal
// grid can be accessed from both the two ways:
// eg: 
//    A | B       A -> D is valid only when both
//    --+--       A -> B -> D is valid and
//    C | D       A -> C -> D is valid
//
// Creeps can can directly go from A to D if Both B and C
// is not occupied by towers.
//
// By introducing the diagonal shortcuts, the routes will
// be more natural.
void GridMap::updateRoute() {

    // horizontal and vertical offsets
    static const int offset_x[] = {-1, 0, 1, 0};
    static const int offset_y[] = {0, 1, 0, -1};
    
    // diagonal offsets
    static const int d_offset_x[] = {-1, -1, 1, 1}; 
    static const int d_offset_y[] = {-1, 1, 1, -1};

    // horizontal and vertical directions
    static const Grid::Direction dirs[] = {
        Grid::RIGHT, Grid::DOWN, Grid::LEFT, Grid::UP
    };

    // diagonal directions
    static const Grid::Direction ddirs[] = {
        Grid::BOTTOMRIGHT, Grid::TOPRIGHT, Grid::TOPLEFT, Grid::BOTTOMLEFT
    };

    // indicate whether the diagonal direction is available
    bool diagonal_valid[4] = {true, true, true, true};

    // Step1: Clear all grids' direction to be Grid::NONE
    clearGridsFlags();

    // Step2: Begin BFS
    std::priority_queue<BFSNode> pq;
    pq.push(BFSNode(_target, 0));

    while (not pq.empty()) {

        // take one node from the queue
        BFSNode node = pq.top();
        pq.pop();

        Coord coord = node.coord;
        unsigned dist = node.dist;

        // Inspect the adjacent nodes
        for (size_t i = 0; i < 4; ++i) {

            // Next node's coordinate
            int next_x = coord.x + offset_x[i];
            int next_y = coord.y + offset_y[i];

            if (isValidCoord(next_x, next_y)) {
                // Update the grid's direction
                _grids[next_y][next_x].setDirection(dirs[i]);
                
                // Push the node into the queue
                pq.push(BFSNode(Coord(next_x, next_y), dist + 1));
                
                // Set the grid as visited
                _visited[next_y][next_x] = true;
            }
        }
    }
}

unsigned GridMap::getWidth() const {
    return _width;
}

unsigned GridMap::getHeight() const {
    return _height;
}


// Clear all grids' directions and mark them as unvisited.
void GridMap::clearGridsFlags() {
    for (size_t i = 0; i < _height; ++i) {
        for (size_t j = 0; j < _width; ++j) {
            _visited[i][j] = false;
            _grids[i][j].setDirection(Grid::NONE);
        }
    }
}

// Determine if the given coordinate is inside the map and
// the corresponding grid has not been visited before.
bool GridMap::isValidCoord(int x, int y) {
    return x >= 0 and x < _width and
           y >= 0 and y < _height and
           not _visited[y][x];
}


#ifdef DEBUG

#include <cstdio>

void GridMap::debugPrint() const {
    for (size_t i = 0; i < _height; ++i) {
        for (size_t j = 0; j < _width; ++j) {
            switch (_grids[i][j].getDirection()) {
                case Grid::LEFT:
                    putchar('<'); break;
                case Grid::RIGHT:
                    putchar('>'); break;
                case Grid::UP:
                    putchar('^'); break;
                case Grid::DOWN:
                    putchar('v'); break;
            }
            putchar(' ');
        }
        puts("");
    }
}

#endif