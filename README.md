# COSC303 Project 4 
Name: Parker Babb

## Build / run instructions

Both programs were built on the Hydra11 machine and can be built with: 

    make

  compiles 'dijkstras.cpp' into 'dijkstras' and 'generate_map.cpp' into 'generate_map' w/ 'g++ -g -Wall -std=gnu++11'.

  'generate_map' generates a random N x N map (with start location at top left and end at bottom right).
  
  Example:

    ./generate_map 100 > map.txt 

  generates a map of size 100 into map.txt


  Run dijkstra's on the map with:

    ./dijkstras < map.txt
    

Test Median Elapsed Time and Median Memory w/ 

     /usr/bin/time -v ./dijkstras < map.txt > /dev/null

  Remove built programs w/ 

    make clean

  
## Benchmark and Methodology

## Benchmark table

| N    | Median Elapsed Time (seconds) | Median Memory (KB) |
|------|-------------------------------|--------------------|
| 10   | 0.00                          | 3456               |
| 20   | 0.00                          | 3456               |
| 50   | 0.00                          | 3712               |
| 100  | 0.01                          | 4224               |
| 200  | 0.06                          | 6656               |
| 500  | 0.44                          | 23944              |
| 1000 | 1.82                          | 85596              |


## Methodology
'generate_map' was run once for an N size of 10, 20, 50, 100, 200, 500, and 1000. Each mapped was saved to 'map(N).txt' and that file was then saved and reused for all trials. The generator picks a random symbol for each cell and is seeded with 'srand(time(NULL))' so that generation of a map results in different sequences.
This seeding idea was a result of debugging with Claude AI, as I realized my map of size 10 was resulting in the same map every run. While the 5 trials were ran on the same map regardless, it ensured a new map was generated each time and was something that sparked my interest. 
Start was defined as the top left (0,0) while end was defined as bottom right (N-1 N-1). The median was calculated by running 5 trials for each N size. 

## Limitations
- Graph is stored using an adjacency list with 4 edges per cell. This uses more memory than simply generating neighbors as needed.
- Input us assumed to be valid for 'generate_map' as no error checking was implemented.
- Due to the seeding of the map being based off of time, if two maps of size N are generated at the same second they will be identical. 


## Reflection

## Contribution
As I had no partner for this project, the implementation of dijkstras.cpp and generate_map.cpp, benchmark running, and README were done by me. I used Claude AI and Geeks for Geeks to further understand the algorithm, help with graph-constructions issues, and debugging both dijkstras.cpp and generate_map.cpp. Used Claude to teach me about rand() and srand() in C++. 
At the end, I asked Claude if my data looked reasonable and had it format the table of results. 

### 1. Graph Representation
Each vertex is one map cell numbered r * cols + c so that an NxN map would generate V = N^2 nodes. For each cell I checked the four neighbors and excluded any that fell outside the map. Each valid neighbor was given a directed edge with a weighted cost of the tile at u. Since the cost was based off leaving said tile, the cost of u->v differed from that of v->u. 
All edges were stored in an adjacency list defined by (neighbor, weight) pairs). 

### 2. Data Structures
I defined a non-traversed edge and any source nodes parents as -1. The path was built by following the parents from the end back to the start then reversing that list. 
A priorityQ min heap defined as (cost, vertex) pairs. It allowed for a node to be pushed more than once if a lower weighted path was found. Already finalized node were skipped.
Vertices were set as finalized when they were popped for the first time, this information was stored in a vector of bools. 

### 3. Complexity Analysis
Total time is O(E log V) and memory is O( V + E) as the heap holds at most E entries and the push/pop operation cost O(log V). 
In terms of N, V = N^2 and each cell has (at most) 4 outgoing edges. Thus, E = 4N^2 -> O(N^2). Time is O(N^2 log N) and memory is O(N^2). Using a heap instead of scanning the entire array prevents the O(V^2) runtime. Using an adjacency list adds O(E) to the memory compared to creating neighbors as needed. 

### 4. Scaling
Time and memory both grew at an expected rate of about N^2. From N = 500 to 1000, time grew at 4.1x and memory at 3.6x while V grew at 4x. This makes sense with a big O of O(N^2 log N). 
Time data on the smaller sizes can be inconclusive based on the table due to N = 10, 20, 50 resulting in a < 0.00s runtime. 

