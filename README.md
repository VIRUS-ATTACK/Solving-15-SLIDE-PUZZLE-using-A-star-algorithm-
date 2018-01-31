# Solving-15-SLIDE-PUZZLE-using-A*-algorithm-
In this project I had implemented a 'c' code to solve 15 slide puzzle using A* algorithm.<br/>
Here the heuristic H(n)=Sum of “number of moves each tile is away from its goal position”.Compile and run the 'AI_optimal(H2).c' file and give the 4x4 input matrix and the output will be:<br/>
1)matrix is solvable matrix or not.<br/>
2)all the matrices in the path of reaching the goal matrix<br/>
3)number of nodes generated(time)<br/>
4)number of nodes present in the memory(space)<br />  
**Here are some of the test cases**<br/>
**TESTCASE-1**<br/>
1 2 4 7<br/>
5 6 3 0<br/>
9 10 11 8<br/>
13 14 15 12<br/><br/>
**TESTCASE-2**<br/>
2 4 3 7<br/>
1 6 10 8<br/>
5 9 0 11<br/>
13 14 15 12<br/><br/>
**TESTCASE-3**<br/>
3 7 0 4<br/>
2 1 8 11<br/>
5 6 10 15 <br/>
9 13 14 12<br/><br/>
**TESTCASE-4**<br/>
2 6 3 4<br/>
1 10 7 8<br/>
5 11 0 12<br/>
9 13 14 15<br/><br/>
**TESTCASE-5**<br/>
2 3 8 4<br/>
1 5 14 12<br/>
11 6 7 15<br/>
9 13 10 0<br/><br/>
**TESTCASE-6**<br/>
1 2 4 8<br/>
7 3 11 10<br/>
0 9 14 12<br/>
5 6 13 15<br/>
# Note:This code only works for solvable 4x4 matrices and for some solvable matrices it takes too much of time.
