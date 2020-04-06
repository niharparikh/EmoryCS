# THIS CODE IS MY OWN WORK, IT WAS WRITTEN WITHOUT CONSULTING A TUTOR OR CODE WRITTEN BY OTHER STUDENTS - Nihar Parikh
# search.py
# ---------
# Licensing Information:  You are free to use or extend these projects for 
# educational purposes provided that (1) you do not distribute or publish 
# solutions, (2) you retain this notice, and (3) you provide clear 
# attribution to UC Berkeley, including a link to 
# http://inst.eecs.berkeley.edu/~cs188/pacman/pacman.html
# 
# Attribution Information: The Pacman AI projects were developed at UC Berkeley.
# The core projects and autograders were primarily created by John DeNero 
# (denero@cs.berkeley.edu) and Dan Klein (klein@cs.berkeley.edu).
# Student side autograding was added by Brad Miller, Nick Hay, and 
# Pieter Abbeel (pabbeel@cs.berkeley.edu).


"""
In search.py, you will implement generic search algorithms which are called
by Pacman agents (in searchAgents.py).
"""

import util

class SearchProblem:
    """
    This class outlines the structure of a search problem, but doesn't implement
    any of the methods (in object-oriented terminology: an abstract class).

    You do not need to change anything in this class, ever.
    """

    def getStartState(self):
        """
        Returns the start state for the search problem
        """
        util.raiseNotDefined()

    def isGoalState(self, state):
        """
          state: Search state

        Returns True if and only if the state is a valid goal state
        """
        util.raiseNotDefined()

    def getchild_nodes(self, state):
        """
          state: Search state

        For a given state, this should return a list of triples,
        (child_node, action, stepCost), where 'child_node' is a
        child_node to the current state, 'action' is the action
        required to get there, and 'stepCost' is the incremental
        cost of expanding to that child_node
        """
        util.raiseNotDefined()

    def getCostOfActions(self, actions):
        """
         actions: A list of actions to take

        This method returns the total cost of a particular sequence of actions.  The sequence must
        be composed of legal moves
        """
        util.raiseNotDefined()


def tinyMazeSearch(problem):
    """
    Returns a sequence of moves that solves tinyMaze.  For any other
    maze, the sequence of moves will be incorrect, so only use this for tinyMaze
    """
    from game import Directions
    s = Directions.SOUTH
    w = Directions.WEST
    return  [s,s,w,s,w,w,s,w]


def depthFirstSearch(problem):
    """
    Search the deepest nodes in the search tree first

    Your search algorithm needs to return a list of actions that reaches
    the goal.  Make sure to implement a graph search algorithm

    To get started, you might want to try some of these simple commands to
    understand the search problem that is being passed in:

    print "Start:", problem.getStartState()
    print "Is the start a goal?", problem.isGoalState(problem.getStartState())
    print "Start's child_nodes:", problem.getchild_nodes(problem.getStartState())
    """

    if problem.isGoalState(problem.getStartState()):
        return []

    # Wanted to use a set instead of a list but kept giving me the error that my state object was not hashable
    closed = []

    fringe = util.Stack()
    fringe.push([(problem.getStartState(), "Stop")])

    while True:

        if fringe.isEmpty():
            return []

        node = fringe.pop()
        last_state = node[len(node) - 1][0]

        if problem.isGoalState(last_state):
            path = []
            for path_actions in node:
                path.append(path_actions[1])
            return path[1:]

        if last_state not in closed:
            closed.append(last_state)

            for child_node in problem.getSuccessors(last_state):
                node_copy = node[:]
                node_copy.append(child_node)
                fringe.push(node_copy)

def breadthFirstSearch(problem):
    """
    Search the shallowest nodes in the search tree first.
    """

    if problem.isGoalState(problem.getStartState()):
        return []

    # Wanted to use a set instead of a list but kept giving me the error that my state object was not hashable
    closed = []

    fringe = util.Queue()
    fringe.push([(problem.getStartState(), "Stop")])

    while True:

        if fringe.isEmpty():
            return []

        node = fringe.pop()
        last_state = node[len(node) - 1][0]


        if problem.isGoalState(last_state):
            path = []
            for path_actions in node:
                path.append(path_actions[1])
            return path[1:]

        if last_state not in closed:
            closed.append(last_state)

            for child_node in problem.getSuccessors(last_state):
                node_copy = node[:]
                node_copy.append(child_node)
                fringe.push(node_copy)

def uniformCostSearch(problem):
    "Search the node of least total cost first. "

    def search_function(item):
        actions = []
        for temp_node in item:
            actions.append(temp_node[1])
        return problem.getCostOfActions(actions[1:])

    if problem.isGoalState(problem.getStartState()):
        return []

    # Wanted to use a set instead of a list but kept giving me the error that my state object was not hashable
    closed = []

    fringe = util.PriorityQueueWithFunction(search_function)
    fringe.push([(problem.getStartState(), "Stop")])

    while True:

        if fringe.isEmpty():
            return []

        node = fringe.pop()
        best_state = node[len(node) - 1][0]

        if problem.isGoalState(best_state):
            path = []
            for path_actions in node:
                path.append(path_actions[1])
            return path[1:]

        if best_state not in closed:
            closed.append(best_state)

            for child_node in problem.getSuccessors(best_state):
                node_copy = node[:]
                node_copy.append(child_node)
                fringe.push(node_copy)

def nullHeuristic(state, problem=None):
    """
    A heuristic function estimates the cost from the current state to the nearest
    goal in the provided SearchProblem.  This heuristic is trivial.
    """
    return 0

def aStarSearch(problem, heuristic=nullHeuristic):
    "Search the node that has the lowest combined cost and heuristic first."

    def search_function(item):
        actions = []
        for temp_node in item:
            actions.append(temp_node[1])
        h = heuristic(item[len(item) - 1][0], problem)
        return problem.getCostOfActions(actions[1:]) + h

    if problem.isGoalState(problem.getStartState()):
        return []

    # Wanted to use a set instead of a list but kept giving me the error that my state object was not hashable
    closed = []

    fringe = util.PriorityQueueWithFunction(search_function)
    fringe.push([(problem.getStartState(), "Stop")])

    while True:

        if fringe.isEmpty():
            return []

        node = fringe.pop()
        best_state = node[len(node) - 1][0]

        if problem.isGoalState(best_state):
            path = []
            for path_actions in node:
                path.append(path_actions[1])
            return path[1:]

        if best_state not in closed:
            closed.append(best_state)

            for child_node in problem.getSuccessors(best_state):
                node_copy = node[:]
                node_copy.append(child_node)
                fringe.push(node_copy)

# Abbreviations
bfs = breadthFirstSearch
dfs = depthFirstSearch
astar = aStarSearch
ucs = uniformCostSearch
