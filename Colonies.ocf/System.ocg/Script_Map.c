/**
 Hex map coordinates and helper functions.

 @author Marky
 */

// Constants for hex tiles and edges
static const MAP_HEX_NORTH_EAST = 0;
static const MAP_HEX_EAST = 1;
static const MAP_HEX_SOUTH_EAST = 2;
static const MAP_HEX_SOUTH_WEST = 3;
static const MAP_HEX_WEST = 4;
static const MAP_HEX_NORTH_WEST = 5;

// Constants for hex nodes
static const MAP_NODE_NORTH = 0;
static const MAP_NODE_NORTH_EAST = 1;
static const MAP_NODE_SOUTH_EAST = 2;
static const MAP_NODE_SOUTH = 3;
static const MAP_NODE_SOUTH_WEST = 4;
static const MAP_NODE_NORTH_WEST = 5;

// Hexes and their surroundings

/** Coordinate modifiers for adjacent hexes of a hex. */
static const MAP_HEX_ADJACENT_HEX_COORDINATES = [[+0, +2], [+2, +2], [+2, +0], [+0, -2], [-2, -2], [-2, 0]];

/** Coordinate modifiers for nodes of a hex. */
static const MAP_HEX_ADJACENT_NODE_COORDINATES = [[+0, +1], [+1, +2], [+2, +1], [+1, +0], [+0, -1], [-1, +0]];

/** Coordinate modifiers for edges of a hex. */
static const MAP_HEX_ADJACENT_EDGE_COORDINATES = [[+0, +1], [+1, +1], [+1, +0], [+0, -1], [-1, -1], [-1, +0]];

// Nodes and their surroundings

/** Coordinate modifiers for adjacent hexes of a node, where the x coordinate is even and the y coordinate is odd. */
static const MAP_NODE_EVEN_ODD_ADJACENT_HEX_COORDINATES = [[-1, +0], [+1, +0], [-1, -1]];

/** Coordinate modifiers for adjacent nodes of a node, where the x coordinate is even and the y coordinate is odd. */
static const MAP_NODE_EVEN_ODD_ADJACENT_NODE_COORDINATES = [[-1, -1], [+1, +1], [+1, -1]];

/** Coordinate modifiers for adjacent edges of a node, where the x coordinate is even and the y coordinate is odd. */
static const MAP_NODE_EVEN_ODD_ADJACENT_NODE_COORDINATES = [[-1, -1], [+0, +0], [+0, -1]];

/** Coordinate modifiers for adjacent hexes of a node, where the x coordinate is odd and the y coordinate is even. */
static const MAP_NODE_ODD_EVEN_ADJACENT_HEX_COORDINATES = [[-2, -1], [+0, +1], [+0, -1]];

/** Coordinate modifiers for adjacent nodes of a node, where the x coordinate is odd and the y coordinate is even. */
static const MAP_NODE_ODD_EVEN_ADJACENT_NODE_COORDINATES = [[-1, +1], [+1, +1], [-1, -1]];

/** Coordinate modifiers for adjacent edges of a node, where the x coordinate is odd and the y coordinate is even. */
static const MAP_NODE_ODD_EVEN_ADJACENT_NODE_COORDINATES = [[-1, +0], [+0, +0], [-1, -1]];

// Edges and their surroundings

/** Coordinate modifiers for adjacent hexes of an edge, where the x coordinate is even and the y coordinate is odd. */
static const MAP_EDGE_EVEN_ODD_ADJACENT_HEX_COORDINATES = [[-1, +0], [+1, +0]];

/** Coordinate modifiers for adjacent nodes of an edge, where the x coordinate is even and the y coordinate is odd. */
static const MAP_EDGE_EVEN_ODD_ADJACENT_NODE_COORDINATES = [[+0, +0], [+1, +1]];

/** Coordinate modifiers for adjacent edges of an edge, where the x coordinate is even and the y coordinate is odd. */
static const MAP_EDGE_EVEN_ODD_ADJACENT_NODE_COORDINATES = [[-1, -1], [+0, -1], [+0, +1], [+1, +1]];

/** Coordinate modifiers for adjacent hexes of an edge, where the x coordinate is odd and the y coordinate is even. */
static const MAP_EDGE_ODD_EVEN_ADJACENT_HEX_COORDINATES = [[+0, -1], [+0, +1]];

/** Coordinate modifiers for adjacent nodes of an edge, where the x coordinate is odd and the y coordinate is even. */
static const MAP_EDGE_ODD_EVEN_ADJACENT_NODE_COORDINATES = [[+0, +0], [+1, +1]];

/** Coordinate modifiers for adjacent edges of an edge, where the x coordinate is odd and the y coordinate is even. */
static const MAP_EDGE_ODD_EVEN_ADJACENT_NODE_COORDINATES = [[-1, -1], [-1, +0], [+1, +1], [+1, +0]];

/** Coordinate modifiers for adjacent hexes of an edge, where the x coordinate is even and the y coordinate is even. */
static const MAP_EDGE_EVEN_EVEN_ADJACENT_HEX_COORDINATES = [[-1, -1], [+1, +1]];

/** Coordinate modifiers for adjacent nodes of an edge, where the x coordinate is even and the y coordinate is even. */
static const MAP_EDGE_EVEN_EVEN_ADJACENT_NODE_COORDINATES = [[+0, +1], [+1, +0]];

/** Coordinate modifiers for adjacent edges of an edge, where the x coordinate is even and the y coordinate is even. */
static const MAP_EDGE_EVEN_EVEN_ADJACENT_NODE_COORDINATES = [[-1, +0], [+0, +1], [+1, +0], [+0, -1]];
