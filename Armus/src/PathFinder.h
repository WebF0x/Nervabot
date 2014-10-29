#ifndef PATHFINDER_H
#define PATHFINDER_H

#include <vector>
#include <set>
#include <libarmus.h>

class PathFinder
{
    public:
    PathFinder(int worldWidth, int worldLength, const std::set<std::pair<int,int> >& goals, const std::set<std::pair<int,int> >& deaths);
    PathFinder(int worldWidth, int worldLength);
    void setGoals(const std::set<std::pair<int,int> >& goals);
    void setDeaths(const std::set<std::pair<int,int> >& deaths);
    void updateWorld();
    void setHeight(int x, int y, int height);
    int getHeight(int x, int y);
    void addDeath(int x, int y);
    void addGoal(int x, int y);
    std::pair<float,float> boxToPoint(int x, int y);
    std::pair<int,int> pointToBox(float x, float y);
    std::pair<float,float> nextWaypoint(float x, float y);
    void debug();

    private:
    static const int GOAL=0;
    static const int DEATH=-1;
    static const int UNKNOWN=-2;

    const int WORLD_WIDTH, WORLD_LENGTH;

    std::vector<std::vector<int> > m_world;
    std::set<std::pair<int,int> > m_goals;  //(x:first, y:second)
    std::set<std::pair<int,int> > m_deaths; //(x:first, y:second)
};


#endif // PATHFINDER_H

