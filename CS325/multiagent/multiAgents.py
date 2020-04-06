# THIS CODE IS MY OWN WORK, IT WAS WRITTEN WITHOUT CONSULTING A TUTOR OR CODE WRITTEN BY OTHER STUDENTS - Nihar Parikh
# multiAgents.py
# --------------
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
#
# Modified by Eugene Agichtein for CS325 Sp 2014 (eugene@mathcs.emory.edu)
#

from util import manhattanDistance
from game import Directions
import random, util

from game import Agent

class ReflexAgent(Agent):
    """
      A reflex agent chooses an action at each choice point by examining
      its alternatives via a state evaluation function.

      The code below is provided as a guide.  You are welcome to change
      it in any way you see fit, so long as you don't touch our method
      headers.
    """


    def getAction(self, gameState):
        """
        You do not need to change this method, but you're welcome to.

        getAction chooses among the best options according to the evaluation function.

        Just like in the previous project, getAction takes a GameState and returns
        some Directions.X for some X in the set {North, South, West, East, Stop}
        """
        # Collect legal moves and successor states
        legalMoves = gameState.getLegalActions()

        # Choose one of the best actions
        scores = [self.evaluationFunction(gameState, action) for action in legalMoves]
        bestScore = max(scores)
        bestIndices = [index for index in range(len(scores)) if scores[index] == bestScore]
        chosenIndex = random.choice(bestIndices) # Pick randomly among the best

        "Add more of your code here if you want to"

        return legalMoves[chosenIndex]

    def evaluationFunction(self, currentGameState, action):
        """
        Design a better evaluation function here.

        The evaluation function takes in the current and proposed successor
        GameStates (pacman.py) and returns a number, where higher numbers are better.

        The code below extracts some useful information from the state, like the
        remaining food (newFood) and Pacman position after moving (newPos).
        Note that the successor game state includes updates such as available food,
        e.g., would *not* include the food eaten at the successor state's pacman position
        as that food is no longer remaining.
        newScaredTimes holds the number of moves that each ghost will remain
        scared because of Pacman having eaten a power pellet.

        Print out these variables to see what you're getting, then combine them
        to create a masterful evaluation function.
        """
        # Useful information you can extract from a GameState (pacman.py)
        successorGameState = currentGameState.generatePacmanSuccessor(action)
        newPos = successorGameState.getPacmanPosition()
        currentFood = currentGameState.getFood() #food available from current state
        newFood = successorGameState.getFood() #food available from successor state (excludes food@successor) 
        currentCapsules=currentGameState.getCapsules() #power pellets/capsules available from current state
        newCapsules=successorGameState.getCapsules() #capsules available from successor (excludes capsules@successor)
        newGhostStates = successorGameState.getGhostStates()
        newScaredTimes = [ghostState.scaredTimer for ghostState in newGhostStates]

        "*** YOUR CODE HERE ***"

        # print newPos
        # print currentFood
        # print newFood
        # print currentCapsules
        # print newCapsules
        # print newGhostStates
        # print newScaredTimes

        score = 0.0
        for ghostState in newGhostStates:
            x = ghostState.getPosition()
            distance_to_ghost = manhattanDistance(x, newPos)
            if distance_to_ghost <= 1:
                score -= 1000

        for food in currentFood.asList():
            distance_to_food = manhattanDistance(food, newPos)
            if distance_to_food == 0:
                score += 100
            else:
                score += 10.0 / distance_to_food

        return score + successorGameState.getScore()


def scoreEvaluationFunction(currentGameState):
    """
      This default evaluation function just returns the score of the state.
      The score is the same one displayed in the Pacman GUI.

      This evaluation function is meant for use with adversarial search agents
      (not reflex agents).
    """
    return currentGameState.getScore()

class MultiAgentSearchAgent(Agent):
    """
      This class provides some common elements to all of your
      multi-agent searchers.  Any methods defined here will be available
      to the MinimaxPacmanAgent, AlphaBetaPacmanAgent & ExpectimaxPacmanAgent.

      You *do not* need to make any changes here, but you can if you want to
      add functionality to all your adversarial search agents.  Please do not
      remove anything, however.

      Note: this is an abstract class: one that should not be instantiated.  It's
      only partially specified, and designed to be extended.  Agent (game.py)
      is another abstract class.
    """

    def __init__(self, evalFn = 'scoreEvaluationFunction', depth = '2'):
        self.index = 0 # Pacman is always agent index 0
        self.evaluationFunction = util.lookup(evalFn, globals())
        self.depth = int(depth)

class MinimaxAgent(MultiAgentSearchAgent):
    """
      Your minimax agent (question 2)
    """

    def getAction(self, gameState):
        """
          Returns the minimax action from the current gameState using self.depth
          and self.evaluationFunction.

          Here are some method calls that might be useful when implementing minimax.

          gameState.getLegalActions(agentIndex):
            Returns a list of legal actions for an agent
            agentIndex=0 means Pacman, ghosts are >= 1

          gameState.generateSuccessor(agentIndex, action):
            Returns the successor game state after an agent takes an action

          gameState.getNumAgents():
            Returns the total number of agents in the game
        """
        "*** YOUR CODE HERE ***"
        num_agents = gameState.getNumAgents()

        def max_value(game_state, at_depth):
            pacman_actions = game_state.getLegalActions(0)
            if game_state.isWin() or at_depth > self.depth or not pacman_actions:
                return self.evaluationFunction(game_state), None
            costs = []
            for action in pacman_actions:
                successor = game_state.generateSuccessor(0, action)
                costs.append((min_value(successor, 1, at_depth)[0], action))

            return max(costs)

        def min_value(game_state, agent_index, at_depth):
            ghost_actions = game_state.getLegalActions(agent_index)
            if game_state.isLose() or at_depth > self.depth or not ghost_actions:
                return self.evaluationFunction(game_state), None
            costs = []
            for action in ghost_actions:
                successor = game_state.generateSuccessor(agent_index, action)
                if agent_index < num_agents - 1:
                    costs.append(min_value(successor, agent_index + 1, at_depth))
                else:
                    costs.append(max_value(successor, at_depth + 1))

            return min(costs)

        return max_value(gameState, 1)[1]

        util.raiseNotDefined()

class AlphaBetaAgent(MultiAgentSearchAgent):
    """
      Your minimax agent with alpha-beta pruning (question 3)
    """

    def getAction(self, gameState):
        """
          Returns the minimax action using self.depth and self.evaluationFunction
        """
        "*** YOUR CODE HERE ***"
        num_agents = gameState.getNumAgents()

        def max_value(game_state, at_depth, alpha, beta):
            pacman_actions = game_state.getLegalActions(0)
            if game_state.isWin() or at_depth > self.depth or not pacman_actions:
                return self.evaluationFunction(game_state), None
            v = (float('-inf'), None)
            for action in pacman_actions:
                successor = game_state.generateSuccessor(0, action)
                cost = min_value(successor, 1, at_depth, alpha, beta)[0]
                if cost > v[0]:
                    v = (cost, action)
                if v[0] > beta:
                    return v
                alpha = max(alpha, v[0])

            return v

        def min_value(game_state, agent_index, at_depth, alpha, beta):
            ghost_actions = game_state.getLegalActions(agent_index)
            if game_state.isLose() or at_depth > self.depth or not ghost_actions:
                return self.evaluationFunction(game_state), None
            v = (float('inf'), None)
            for action in ghost_actions:
                successor = game_state.generateSuccessor(agent_index, action)
                if agent_index < num_agents - 1:
                    cost = min_value(successor, agent_index + 1, at_depth, alpha, beta)[0]
                else:
                    cost = max_value(successor, at_depth + 1, alpha, beta)[0]
                if cost < v[0]:
                    v = (cost, action)
                if v[0] < alpha:
                    return v
                beta = min(beta, v[0])

            return v

        starting_alpha = float('-inf')
        starting_beta = float('inf')
        return max_value(gameState, 1, starting_alpha, starting_beta)[1]

        util.raiseNotDefined()

class ExpectimaxAgent(MultiAgentSearchAgent):
    """
      Your expectimax agent (question 4)
    """

    def getAction(self, gameState):
        """
          Returns the expectimax action using self.depth and self.evaluationFunction

          All ghosts should be modeled as choosing uniformly at random from their
          legal moves.
        """
        "*** YOUR CODE HERE ***"
        num_agents = gameState.getNumAgents()

        def max_value(game_state, at_depth):
            pacman_actions = game_state.getLegalActions(0)
            for move in pacman_actions:
                if move == Directions.STOP:
                    pacman_actions.remove(move)
            if game_state.isWin() or at_depth > self.depth or not pacman_actions:
                return self.evaluationFunction(game_state), None
            costs = []
            for action in pacman_actions:
                successor = game_state.generateSuccessor(0, action)
                costs.append((min_value(successor, 1, at_depth)[0], action))

            return max(costs)

        def min_value(game_state, agent_index, at_depth):
            ghost_actions = game_state.getLegalActions(agent_index)
            if game_state.isLose() or at_depth > self.depth or not ghost_actions:
                return self.evaluationFunction(game_state), None
            costs = []
            for action in ghost_actions:
                successor = game_state.generateSuccessor(agent_index, action)
                if agent_index < num_agents - 1:
                    costs.append(min_value(successor, agent_index + 1, at_depth))
                else:
                    costs.append(max_value(successor, at_depth + 1))

            total_cost = 0.0
            for cost in costs:
                total_cost = total_cost + cost[0]
            total_cost = total_cost / len(costs)

            return total_cost, None

        return max_value(gameState, 1)[1]

        util.raiseNotDefined()

def betterEvaluationFunction(currentGameState):
    """
      Your extreme ghost-hunting, pellet-nabbing, food-gobbling, unstoppable
      evaluation function (question 5).

      DESCRIPTION: Evaluated ghosts position and whether or not they were scared, then if capsule was eaten, then evaluated if food was eaten and distance to food using inverse
      Then finally added count to value food when its less than 4, as saw that pacman got stuck often at the end.
    """
    "*** YOUR CODE HERE ***"

    currentPos = currentGameState.getPacmanPosition()
    currentFood = currentGameState.getFood()  # food available from current state
    currentCapsules = currentGameState.getCapsules()  # power pellets/capsules available from current state
    currentGhostStates = currentGameState.getGhostStates()
    currentScaredTimes = [ghostState.scaredTimer for ghostState in currentGhostStates]

    score = 0.0

    if len(currentFood.asList()) < 4:
        score += 10

    for ghostState in currentGhostStates:
        x = ghostState.getPosition()
        distance_to_ghost = manhattanDistance(x, currentPos)
        if distance_to_ghost <= 5:
            if ghostState.scaredTimer > 0:
                score += 100
            else:
                score -= 10
            if distance_to_ghost <= 2:
                if ghostState.scaredTimer > 0:
                    score += 200
                else:
                    score -= 20

    for food in currentFood.asList():
        distance_to_food = manhattanDistance(food, currentPos)
        # if distance_to_food == 0:
        #     score += 1000
        # else:
        score += 10.0 / distance_to_food

    for capsule in currentCapsules:
        distance_to_capsule = manhattanDistance(capsule, currentPos)
        if distance_to_capsule == 0:
            score += 10

    # food_action = False
    # for action in currentGameState.getLegalActions(0):
    #     successor = currentGameState.generateSuccessor(0, action)
    #     if len(successor.getFood().asList()) < len(currentFood.asList()) and not food_action:
    #         food_action = True
    #         score += 100

    return score + currentGameState.getScore()

    util.raiseNotDefined()

# Abbreviation
better = betterEvaluationFunction

class ContestAgent(MultiAgentSearchAgent):
    """
      Your agent for the mini-contest
    """

    def getAction(self, gameState):
        """
          Returns an action.  You can use any method you want and search to any depth you want.
          Just remember that the mini-contest is timed, so you have to trade off speed and computation.

          Ghosts don't behave randomly anymore, but they aren't perfect either -- they'll usually
          just make a beeline straight towards Pacman (or away from him if they're scared!)
        """
        "*** YOUR CODE HERE ***"
        util.raiseNotDefined()

