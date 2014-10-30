#include "PathFinder.h"

using namespace std;

PathFinder::PathFinder(int worldWidth, int worldLength, float realWorldWidth, float realWorldLength) : WORLD_WIDTH(worldWidth), WORLD_LENGTH(worldLength), REAL_WORLD_WIDTH(realWorldWidth), REAL_WORLD_LENGTH(realWorldLength)
{
    m_world = vector<vector<int> >(WORLD_WIDTH, vector<int>(WORLD_LENGTH,UNKNOWN));
}

void PathFinder::setGoals(const set<pair<int,int> >& goals)
{
    m_goals = goals;
}

void PathFinder::setDeaths(const set<pair<int,int> >& deaths)
{
    m_deaths = deaths;
}

void PathFinder::updateWorld()
{
    m_world = vector<vector<int> >(WORLD_WIDTH, vector<int>(WORLD_LENGTH,UNKNOWN));
    for(set<pair<int,int> >::iterator death=m_deaths.begin(); death!=m_deaths.end(); ++death)
    {
        int x = death->first;
        int y = death->second;
        setHeight(x,y,DEATH);
    }

    int height = GOAL;
    while(!m_goals.empty())
    {
    	set<pair<int,int> > nextGoals;

        for(set<pair<int,int> >::iterator goal=m_goals.begin(); goal!=m_goals.end(); ++goal)
        {
            int x = goal->first;
            int y = goal->second;

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

//Don't forget to call updateWorld() when done!
void PathFinder::addDeath(int x, int y)
{
    m_deaths.insert(make_pair(x,y));
}
void PathFinder::addGoal(int x, int y)
{
    m_goals.insert(make_pair(x,y));
}

void PathFinder::debug()
{
	LCD_Printf("NbDeath: %d\n", m_deaths.size() );
}

/*
 * Returns center of box(x,y) in real world coordinates
 */
pair<float,float> PathFinder::boxToPoint(int x, int y)
{
	float resultX = ((float)x +.5f) * REAL_WORLD_WIDTH/WORLD_WIDTH;
	float resultY = ((float)y +.5f) * REAL_WORLD_LENGTH/WORLD_LENGTH;

	return make_pair(resultX, resultY);
}

/*
 * Returns box containing point(x,y)
 */
pair<int,int> PathFinder::pointToBox(float x, float y)
{
	int resultX = x*WORLD_WIDTH/REAL_WORLD_WIDTH;
	int resultY = y*WORLD_LENGTH/REAL_WORLD_LENGTH;

	return make_pair(resultX, resultY);
}

/*
 * Returns the real world coordinates of a more interesting neighbor point
 */
pair<float,float> PathFinder::nextWaypoint(float x, float y)
{
	pair<int,int> currentBox = pointToBox(x,y);
	int boxX = currentBox.first;
	int boxY = currentBox.second;
	int currentHeight = getHeight(boxX, boxY);

	set<pair<int,int> > boxesToCheck;
	boxesToCheck.insert(make_pair(boxX-1,boxY));
	boxesToCheck.insert(make_pair(boxX+1,boxY));
	boxesToCheck.insert(make_pair(boxX,boxY-1));
	boxesToCheck.insert(make_pair(boxX,boxY+1));

	pair<int,int> bestBox = currentBox;
	int bestHeight = currentHeight;

	for(set<pair<int,int> >::iterator neighborBox=boxesToCheck.begin(); neighborBox!=boxesToCheck.end(); ++neighborBox)
	{
		int neighborX = neighborBox->first;
		int neighborY = neighborBox->second;
		int neighborHeight = getHeight(neighborX, neighborY);

		bool neighborIsBetter;

		switch(bestHeight)
		{
			case UNKNOWN:
			{
				neighborIsBetter = (neighborHeight!=UNKNOWN);
				break;
			}
			case DEATH:
			{
				neighborIsBetter = (neighborHeight!=UNKNOWN && neighborHeight!=DEATH);
				break;
			}
			default:
			{
				neighborIsBetter = (neighborHeight < bestHeight && neighborHeight!=UNKNOWN && neighborHeight!=DEATH);
				break;
			}
		}

		if(neighborIsBetter)
		{
			bestBox = make_pair(neighborX, neighborY);
			bestHeight = neighborHeight;
		}
	}

	return boxToPoint(bestBox.first,bestBox.second);

/*

	//int height;



	if(currentHeight == DEATH || currentHeight == UNKNOWN)
	{
		pair<int,int> bestBox = make_pair(boxX, boxY);
		height = getHeight(boxX-1,boxY);LCD_Printf("height: %d\n", height);
		if(height < currentHeight && height!=UNKNOWN && height!=DEATH) return boxToPoint(boxX-1,boxY);
	}

	LCD_Printf("currentHeight: %d\n", currentHeight);

	height = getHeight(boxX-1,boxY);LCD_Printf("height: %d\n", height);
	if(height < currentHeight && height!=UNKNOWN && height!=DEATH) return boxToPoint(boxX-1,boxY);

	height = getHeight(boxX+1,boxY);LCD_Printf("height: %d\n", height);
	if(height < currentHeight && height!=UNKNOWN && height!=DEATH) return boxToPoint(boxX+1,boxY);

	height = getHeight(boxX,boxY+1);LCD_Printf("height: %d\n", height);
	if(height < currentHeight && height!=UNKNOWN && height!=DEATH) return boxToPoint(boxX,boxY+1);

	height = getHeight(boxX,boxY-1);LCD_Printf("height: %d\n", height);
	if(height < currentHeight && height!=UNKNOWN && height!=DEATH) return boxToPoint(boxX,boxY-1);

	return boxToPoint(boxX,boxY);
	*/
}

