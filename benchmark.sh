#!/bin/bash
# Josh Nithsdale (s3346764@student.rmit.edu.au)

HEIGHT=2000
WIDTH=2000
SEED=0
NUMRUNS=10


COUNTER=0
echo "========= Doing recursive svg ========="
while [ $COUNTER -lt $NUMRUNS ]; do
    echo "++++ Run $COUNTER ++++"
    ./src/maze --gr $SEED $HEIGHT $WIDTH --sv recursive.svg
    let COUNTER=COUNTER+1
done

COUNTER=0
echo "========= Doing recursive bin ========="
while [ $COUNTER -lt $NUMRUNS ]; do
    echo "++++ Run $COUNTER ++++"
    ./src/maze --gr $SEED $HEIGHT $WIDTH --sb recursive.maze
    let COUNTER=COUNTER+1
done

COUNTER=0
echo "========= Doing kruskal svg ========="
while [ $COUNTER -lt $NUMRUNS ]; do
    echo "++++ Run $COUNTER ++++"
    ./src/maze --gk $SEED $HEIGHT $WIDTH --sv kruskal.svg
    let COUNTER=COUNTER+1
done

COUNTER=0
echo "========= Doing kruskal bin ========="
while [ $COUNTER -lt $NUMRUNS ]; do
    echo "++++ Run $COUNTER ++++"
    ./src/maze --gk $SEED $HEIGHT $WIDTH --sb kruskal.maze
    let COUNTER=COUNTER+1
done

COUNTER=0
echo "========= Doing depth first solve on recursive ========="
while [ $COUNTER -lt $NUMRUNS ]; do
    echo "++++ Run $COUNTER ++++"
    ./src/maze --lb recursive.maze --pd --sv recursive_solved.svg
    let COUNTER=COUNTER+1
done

COUNTER=0
echo "========= Doing breadth first solve on recursive ========="
while [ $COUNTER -lt $NUMRUNS ]; do
    echo "++++ Run $COUNTER ++++"
    ./src/maze --lb recursive.maze --pb --sv recursive_solved.svg
    let COUNTER=COUNTER+1
done

COUNTER=0
echo "========= Doing A star solve on recursive ========="
while [ $COUNTER -lt $NUMRUNS ]; do
    echo "++++ Run $COUNTER ++++"
    ./src/maze --lb recursive.maze --pa --sv recursive_solved.svg
    let COUNTER=COUNTER+1
done

COUNTER=0
echo "========= Doing depth first solve on kruskal ========="
while [ $COUNTER -lt $NUMRUNS ]; do
    echo "++++ Run $COUNTER ++++"
    ./src/maze --lb kruskal.maze --pd --sv kruskal_solved.svg
    let COUNTER=COUNTER+1
done

COUNTER=0
echo "========= Doing breadth first solve on kruskal ========="
while [ $COUNTER -lt $NUMRUNS ]; do
    echo "++++ Run $COUNTER ++++"
    ./src/maze --lb kruskal.maze --pb --sv kruskal_solved.svg
    let COUNTER=COUNTER+1
done

COUNTER=0
echo "========= Doing A star solve on kruskal ========="
while [ $COUNTER -lt $NUMRUNS ]; do
    echo "++++ Run $COUNTER ++++"
    ./src/maze --lb kruskal.maze --pa --sv kruskal_solved.svg
    let COUNTER=COUNTER+1
done
