# COSC303 Project 4 
Name: Parker Babb

## Build / run instructions

Both programs can be built with: 

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


##Methodology
'generate_map' was run once for an N size of 10, 20, 50, 100, 200, 500, and 1000. Each maped was saved to 'map(N).txt' and that file was then cleared and reused for all trails. The generator picks a random symbol for each cell and is seeded with 'srand(time(NULL))' so that generation of a map results in different sequences.
This seeding idea was a result of debugging with Claude AI, as I realized my map of size 10 was resulting in the same map every run. While this wouldn't skew any gathered data due to the table representing one run of each size, it was something that I figured should be resolved. 


## Reflection

##Contrib
