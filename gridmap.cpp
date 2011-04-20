#include "coord.h"
#include "grid.h"
#include "gridmap.h"

#include <cstdlib>
#include <cstdio>
#include <queue>
#include <unistd.h>

// struct BFSNode
// Data fields:
//     Coord coord: coordinate of this node
//     int dist: distance from the source node to this node
// Used in GridMap::updateRoute()
struct BFSNode {
    BFSNode(Coord coord, int dist)
        :coord(coord),
         dist(dist) {}
    bool operator<(const BFSNode &rhs) const {
        return dist > rhs.dist;
    }
    Coord coord;
    int dist;
};


// GridMap constructor 
GridMap::GridMap(int width, int height)
    :_width(width),
     _height(height),
     _grids(NULL),
     _visited(NULL) {
    // construct a two dimensional array of grids and visit
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
        delete [] _grids[i];
        delete [] _visited[i];
    }
    delete [] _grids;
    delete [] _visited;
}

// Set the target coordinate of the map
void GridMap::setTarget(int x, int y) {
    _target = Coord(x, y);
}

// Update the routes, this method is called each time
// a new tower is built or a present tower is destroyed.
//
// This method uses a variant of Breadth-First Search to
// calculate the routes.
//
// To begin with, the target node is pushed into the priority
// queue with distance 0. While the priorit queue is not
// empty, at each iteration, the node with minimal distance will 
// be popped from the queue. Then its adjacent nodes will
// be inspected. For each adjacent node, if it has not been
// visited before, it will be pushed into the queue with the
// new distance and its direction and visited flag will be set.
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

    // Correspondencies between index and position
    // 
    //     offset              d_offset:      
    //  +---+---+---+        +---+---+---+
    //  |   | 3 |   |        | 0 |   | 3 | 
    //  +---+---+---+        +---+---+---+
    //  | 0 |   | 2 |        |   |   |   |
    //  +---+---+---+        +---+---+---+
    //  |   | 1 |   |        | 1 |   | 2 |
    //  +---+---+---+        +---+---+---+
    // 
    // if offset[i] is invalid, then
    // d_offset[i] and 
    // d_offset[(i + 1) % 4] is invalid.

    // horizontal and vertical directions
    static const Grid::Direction dirs[] = {
        Grid::RIGHT, Grid::UP, Grid::LEFT, Grid::DOWN
    };

    // diagonal directions
    static const Grid::Direction ddirs[] = {
        Grid::BOTTOMRIGHT, Grid::TOPRIGHT, Grid::TOPLEFT, Grid::BOTTOMLEFT
    };

    // indicate whether the diagonal direction is available
    bool diagonal_valid[] = {true, true, true, true};

    // Step1: Clear all grids' direction to be Grid::NONE
    //        and mark all grids as un-visited
    clearGridsFlags();

    // Step2: Begin BFS
    std::priority_queue<BFSNode> pq;
    pq.push(BFSNode(_target, 0));
    _visited[_target.y][_target.x] = true;

    while (not pq.empty()) {

        // take one node from the queue
        BFSNode node = pq.top();
        pq.pop();

        Coord coord = node.coord;
        int dist = node.dist;

        // Inspect the adjacent nodes
        for (size_t i = 0; i < 4; ++i) {

            // Next node's coordinate
            int next_x = coord.x + offset_x[i];
            int next_y = coord.y + offset_y[i];

            if (isValidCoord(next_x, next_y)) {

                if (not _visited[next_y][next_x]) {
                    // Update the grid's direction
                    _grids[next_y][next_x].setDirection(dirs[i]);
                    
                    // Push the node into the queue
                    pq.push(BFSNode(Coord(next_x, next_y), dist + 10));
                    
                    // Mark the grid as visited
                    _visited[next_y][next_x] = true;
                }

            } else {
                // The coordinate is invalid 
                // Thus the corresponding diagonal route is invalid
                diagonal_valid[i] = false;
                diagonal_valid[(i + 1) % 4] = false;
            }
        }

        // Further inspect the diagonally adjacent nodes
        for (size_t i = 0; i < 4; ++i) {

            if (diagonal_valid[i]) {

                int next_x = coord.x + d_offset_x[i];
                int next_y = coord.y + d_offset_y[i];

                if (not _visited[next_y][next_x]) {
                    // Update the grid's direction
                    _grids[next_y][next_x].setDirection(ddirs[i]);

                    // Push the node into the queue
                    pq.push(BFSNode(Coord(next_x, next_y), dist + 14));

                    // Mark the grid as visited
                    _visited[next_y][next_x] = true;
                }
            } 
        }
    }
}

int GridMap::getWidth() const {
    return _width;
}

int GridMap::getHeight() const {
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

// Determine if the given coordinate is inside the map
bool GridMap::isValidCoord(int x, int y) {
    return x >= 0 and x < _width and
           y >= 0 and y < _height;
}


#ifdef DEBUG

#include <cstdio>

void GridMap::debugPrint() const {
    printf("   ");
    for (size_t i = 0; i < _width; ++i) {
        printf("%3d", i);
    }
    puts("");
    for (size_t i = 0; i < _height; ++i) {
        printf("%3d ", i);
        for (size_t j = 0; j < _width; ++j) {
            switch (_grids[i][j].getDirection()) {
                case Grid::NONE:
                    putchar('+'); break;
                case Grid::LEFT:
                    putchar('<'); break;
                case Grid::RIGHT:
                    putchar('>'); break;
                case Grid::UP:
                    putchar('^'); break;
                case Grid::DOWN:
                    putchar('v'); break;
                case Grid::TOPLEFT:
                case Grid::BOTTOMRIGHT:
                    putchar('\\'); break;
                default:
                    putchar('/'); break;
            }
            putchar(' ');
        }
        puts("");
    }
}

#endif
