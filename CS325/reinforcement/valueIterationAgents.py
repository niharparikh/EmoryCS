# THIS CODE IS MY OWN WORK, IT WAS WRITTEN WITHOUT CONSULTING A TUTOR OR CODE WRITTEN BY OTHER STUDENTS - Nihar Parikh
# valueIterationAgents.py
# -----------------------
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


import mdp, util

from learningAgents import ValueEstimationAgent

class ValueIterationAgent(ValueEstimationAgent):
    """
        * Please read learningAgents.py before reading this.*

        A ValueIterationAgent takes a Markov decision process
        (see mdp.py) on initialization and runs value iteration
        for a given number of iterations using the supplied
        discount factor.
    """
    def __init__(self, mdp, discount = 0.9, iterations = 100):
        """
          Your value iteration agent should take an mdp on
          construction, run the indicated number of iterations
          and then act according to the resulting policy.

          Some useful mdp methods you will use:
              mdp.getStates()
              mdp.getPossibleActions(state)
              mdp.getTransitionStatesAndProbs(state, action)
              mdp.getReward(state, action, nextState)
              mdp.isTerminal(state)
        """
        self.mdp = mdp
        self.discount = discount
        self.iterations = iterations
        self.values = util.Counter() # A Counter is a dict with default 0

        # Write value iteration code here
        "*** YOUR CODE HERE ***"

        states = self.mdp.getStates()

        for i in range(iterations):
            temp = util.Counter()

            for state in states:
                best = float("-inf")
                actions = self.mdp.getPossibleActions(state)

                for action in actions:
                    transitions = self.mdp.getTransitionStatesAndProbs(state, action)
                    total = 0

                    for transition in transitions:
                        next_state = transition[0]
                        next_prob = transition[1]
                        reward = self.mdp.getReward(state, action, next_state)
                        total += (reward + (discount * self.values[next_state])) * next_prob

                    best = max(best, total)

                if best != float("-inf"):
                    temp[state] = best

            for state in states:
                self.values[state] = temp[state]


    def getValue(self, state):
        """
          Return the value of the state (computed in __init__).
        """
        return self.values[state]


    def computeQValueFromValues(self, state, action):
        """
          Compute the Q-value of action in state from the
          value function stored in self.values.
        """
        "*** YOUR CODE HERE ***"

        transitions = self.mdp.getTransitionStatesAndProbs(state, action)
        total = 0

        for transition in transitions:
            next_state = transition[0]
            next_prob = transition[1]
            reward = self.mdp.getReward(state, action, next_state)
            total += (reward + (self.discount * self.values[next_state])) * next_prob

        return total

        util.raiseNotDefined()

    def computeActionFromValues(self, state):
        """
          The policy is the best action in the given state
          according to the values currently stored in self.values.

          You may break ties any way you see fit.  Note that if
          there are no legal actions, which is the case at the
          terminal state, you should return None.
        """
        "*** YOUR CODE HERE ***"

        best = float("-inf")
        best_action = None
        actions = self.mdp.getPossibleActions(state)

        if len(actions) == 0:
            return best_action

        for action in actions:
            q_val = self.computeQValueFromValues(state, action)
            if q_val > best:
                best = q_val
                best_action = action

        return best_action

        util.raiseNotDefined()

    def getPolicy(self, state):
        return self.computeActionFromValues(state)

    def getAction(self, state):
        "Returns the policy at the state (no exploration)."
        return self.computeActionFromValues(state)

    def getQValue(self, state, action):
        return self.computeQValueFromValues(state, action)
