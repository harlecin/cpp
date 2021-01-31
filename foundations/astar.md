# A* Search Algorithm

In this post I want to discuss the a* algorithm (pronounced 'a-star'), how it is used for motion planning and how we can implement it in cpp.

The process of determining how to get from a start to an endpoint is called 'planning' and for a robot it's called 'robot motion planning'. There are two broad categories:

- discrete motion planning
- continuous motion planning

The planning problem is formulated as follows: Given a:

- map
- starting location
- end location
- cost function (e.g. shortest, quickest or 'safest' path)

> Goal: Find the minimum cost path

We can frame the path planning problem as a search problem. Imagine we have the following map:

```
S    ⛰️    0    0    0    0
0    ⛰️    0    0    0    0
0    ⛰️    0    0    0    0
0    ⛰️    0    0    0    0
0    0     0    0    ⛰️   G
```
With S(tart) and G(oal) and obstacles in the form of little mountains. Our robot is allowed to travel all points represented by 0 and can only go: up/down, left/right. Our goal is to get from S to G with the minimum number of actions.

Let's assume point S has coordinates (0,0). In this case I have only one valid next step: going to point (1,0). Going there costs me one movement point. We will call the sum of the movement points g-value. For every next planned move (every expansion), we start from the point with the smallest g-value. The g-value when the robot hits the Goal is equivalent to the number of steps it has to take in total. This basically amounts to trying every available path, which is not super efficient to put it mildly:)

The a* algorithm comes to the rescue. In order to explore the available options more efficiently, a* uses a heuristic function `h(x,y)` that measures the distance from a given point `(x,y)` to the goal, if there were no obstacles present.

The following map shows the h-value for each point on our map:
```
S    8    7    6    5    4
8    7    6    5    4    3
7    6    5    4    3    2
6    5    4    3    2    1
5    4    3    2    1    G   
```
The actual distance to the goal is therefore always strictly larger or equal to `h(x,y)`:
$$
h(x,y) \leq \text{distance to goal from (x,y)}
$$

We know keep track of the g-value and of the sum of g-value + heuristic-function value, which we will call f-value. So starting from `(0,0)` we have `(0, 0+9)`.

So the f-value tells us, how many steps would it take in total, given that it already took a certain number of steps to reach the current point, to get to the goal if there were no obstacles present. So in essence, the f-value is the most optimistic estimate we have to reach our goal, given our current location. Let's take a look at a concrete example using our map:

Image you are currently at location L. I added the g-value and the heuristic value for our two next possible moves (g, h):
```
S    ⛰️    0    0    0    0
0    ⛰️    0    0    0    0
0    ⛰️    0    0    0    0
0    ⛰️  (7,4)  0    0    0
0    0     L   (7,2) ⛰️   G
```
Your g-value at L is 6, the f-value is 9 (6+3). Should we go up or to the right? If we go to the right, we get: (7,7+2) whereas if we go up, we get (7, 7+4). So a* will go right, because we do not want to move away from our goal.