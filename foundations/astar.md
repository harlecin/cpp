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
With S(tart) and G(oal) and obstacles in the form of little mountains. Our robot is allowed to travel all points represented by 0 and can only go: up/down, left/right.