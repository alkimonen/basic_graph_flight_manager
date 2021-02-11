/**
 * Title : Balanced Search Trees , Hashing and Graphs
 * Author : Alkým Önen
 * Description : Source code of Graph
 */

#include <string>
#include <iostream>
#include "graph.h"
/*Do not add new libraries or files*/

Graph::Graph()
{
    adjList.clear();
}  // end constructor

void Graph::addAirport(const string& airportName)
{
    map< string, list<node> >::iterator ite;
    ite = adjList.find( airportName);
    if ( ite == adjList.end() )
    {
        list<node> emptyList;
        adjList.insert( pair< string, list<node> >( airportName, emptyList));
    }
}  // end addPerformer

void Graph::addConnection(const string& airport1, const string& airport2, int numOfPassengers)
{
    map< string, list<node> >::iterator airportIte1;
    airportIte1 = adjList.find( airport1);

    map< string, list<node> >::iterator airportIte2;
    airportIte2 = adjList.find( airport2);

    if ( ( airportIte1 != adjList.end() ) && ( airportIte2 != adjList.end() ) )
    {
        node airportNode1;
        airportNode1.airportName = airport2;
        airportNode1.numOfPassengers = numOfPassengers;
        airportIte1->second.push_back( airportNode1);

        node airportNode2;
        airportNode2.airportName = airport1;
        airportNode2.numOfPassengers = numOfPassengers;
        airportIte2->second.push_back( airportNode2);
    }
}  // end addConnection

list<string> Graph::getAdjacentAirports(const string& airportName)
{
    list<string> result;
    map< string, list<node> >::iterator airportIte;
    airportIte = adjList.find( airportName);

    if( airportIte != adjList.end() )
    {
        list<node>::iterator nodeIte;
        for ( nodeIte = airportIte->second.begin(); nodeIte != airportIte->second.end(); ++nodeIte)
        {
            result.push_back( nodeIte->airportName);
        }
    }
    return result;
}  // end getAdjacentAirports

int Graph::getTotalPassengers(const string& airportName)
{
    int result = 0;
    map< string, list<node> >::iterator airportIte;
    airportIte = adjList.find( airportName);

    if( airportIte != adjList.end() )
    {
        list<node>::iterator nodeIte;
        for ( nodeIte = airportIte->second.begin(); nodeIte != airportIte->second.end(); ++nodeIte)
        {
            result += nodeIte->numOfPassengers;
        }
    }
    return result;
}  // end getTotalPassengers


list<string> Graph::findShortestPath(const string& airport1, const string& airport2)
{
    list<string> currentPath;
    list<string> returnBack;
    list<string> visited;
    list<string> noPath;
    string currentAirport;
    bool add;
    bool exit = false;

    map< string, list<node> >::iterator start;
    map< string, list<node> >::iterator finish;

    start = adjList.find( airport1);
    finish = adjList.find( airport2);

    if  ( !( airport1.compare( airport2) == 0 ) && ( start != adjList.end() ) && ( finish != adjList.end() ) )
    {
        currentAirport = airport1;
        currentPath.push_back( currentAirport);

        list<node> adjacentAirports = start->second;
        list<node> lastList = finish->second;

        list<node>::iterator airportIte = adjacentAirports.begin();


        while ( !exit )
        {
            visited.push_back( currentAirport);
            if ( currentAirport != airport1)
            {
                airportIte++;
            }

            for ( list<node>::iterator ite = lastList.begin(); ite != lastList.end(); ++ite )
            {
                if ( ite->airportName == currentAirport )
                {
                    currentPath.push_back( airport2);
                    return currentPath;
                }
            }

            if ( airportIte == adjacentAirports.end() && returnBack.empty() )
            {
                exit = true;
            }
            else
            {
                if ( airportIte == adjacentAirports.end() )
                {
                    if ( currentAirport != airport1 )
                    {
                        currentPath.pop_back();
                    }
                    currentPath.pop_back();

                    currentAirport = returnBack.front();
                    returnBack.pop_front();

                    currentPath.push_back( currentAirport);
                    adjacentAirports = ( adjList.find( currentAirport))->second;
                    airportIte = adjacentAirports.begin();

                    currentAirport = airportIte->airportName;
                }
                else
                {
                    if ( currentAirport != airport1 )
                    {
                        currentPath.pop_back();
                    }

                    currentAirport = airportIte->airportName;
                    currentPath.push_back( currentAirport);

                    add = true;
                    for ( list<node>::iterator ite = visited.begin(); ite != visited.end(); ++ite )
                    {
                        if ( ite->airportName == currentAirport )
                        {
                            add = false;
                        }
                    }

                    if ( add )
                    {
                        returnBack.push_back( currentAirport);
                        visited.push_back( currentAirport);
                    }
                }
            }
        }
    }
    return noPath;
}  // end findShortestPath

list< pair<string, string> > Graph::findMST()
{   /*YOUR IMPLEMENTATION*/
    list< pair<string, string> > result;

    return result;
}  // end findMST

void Graph::deleteAirport(const string& airportName)
{
    string name;
    map< string, list<node> >::iterator ite;
    ite = adjList.find( airportName);

    if ( ite != adjList.end() )
    {
        while ( ! (ite->second.empty()) )
        {
            map< string, list<node> >::iterator current = adjList.find( name);
            if ( current != adjList.end() )
            {
                for( list<node>::iterator i = current->second.begin(); i !=  (current->second).end(); ++i )
                {
                    if( airportName.compare( i->airportName) == 0 )
                    {
                        current->second.erase(i);
                    }
                }
            }
            ite->second.pop_front();
        }
        adjList.erase( airportName);
    }

}  // end deleteAirport

