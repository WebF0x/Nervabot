/*

#include "PathFinder.h"

using namespace std;

PathFinder::PathFinder(int worldWidth, int worldLength, const set<pair<int,int>>& goals, const set<pair<int,int>>& deaths) : WORLD_WIDTH(worldWidth), WORLD_LENGTH(worldLength)
{
    setGoals(goals);
    setDeaths(deaths);
    m_world = vector<vector<int>>(WORLD_WIDTH, vector<int>(WORLD_LENGTH,UNKNOWN));
}

void PathFinder::setGoals(const set<pair<int,int>>& goals)
{
    m_goals = goals;
}

void PathFinder::setDeaths(const set<pair<int,int>>& deaths)
{
    m_deaths = deaths;
}

void PathFinder::updateWorld()
{
    m_world = vector<vector<int>>(WORLD_WIDTH, vector<int>(WORLD_LENGTH,UNKNOWN));

    for(auto death : m_deaths)
    {
        int x = death.first;
        int y = death.second;
        setHeight(x,y,DEATH);
    }

    int height = GOAL;
    while(!m_goals.empty())
    {
        decltype(m_goals) nextGoals;

        for(auto goal : m_goals)
        {
            int x = goal.first;
            int y = goal.second;

            if(getHeight(x,y) == UNKNOWN)
            {
                setHeight(x,y, height);

                if(getHeight(x+1,y) == UNKNOWN) nextGoals.insert(make_pair(x+1,y));
                if(getHeight(x-1,y) == UNKNOWN) nextGoals.insert(make_pair(x-1,y));
                if(getHeight(x,y+1) == UNKNOWN) nextGoals.insert(make_pair(x,y+1));
                if(getHeight(x,y-1) == UNKNOWN) nextGoals.insert(make_pair(x,y-1));
            }
        }
        m_goals = nextGoals;
        ++height;
    }
}

void PathFinder::setHeight(int x, int y, int height)
{
    if(x>=0 && y>=0 && x<WORLD_WIDTH && y<WORLD_LENGTH && (height==UNKNOWN || height==DEATH || height==GOAL || height>0))
    {
        m_world.at(x).at(y) = height;
    }
}

int PathFinder::getHeight(int x, int y)
{
    if(x>=0 && y>=0 && x<WORLD_WIDTH && y<WORLD_LENGTH)
    {
        return m_world.at(x).at(y);
    }
    else
    {
        return DEATH;
    }
}

void PathFinder::printWorld()
{
    for(auto line : m_world)
    {
        for(auto height : line)
        {
            if(height==UNKNOWN) cout<<'?';
            else if(height==GOAL) cout<<'*';
            else if(height==DEATH) cout<<'X';
            else cout<<height;
            cout<<'\t';
        }
        cout<<endl;
    }
}

//Don't forget to call updateWorld() when done!
void PathFinder::addDeath(int x, int y)
{
    m_deaths.insert(make_pair(x,y));
}

*/
