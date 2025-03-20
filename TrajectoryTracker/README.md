# Introduction
This is going to serve as a detailed explanation to solve the presented challenge. I will outline the models, assumptions, and main workflow, among other things. I will provide an in-depth explanation of the key algorithms and data structures used in developing this solution.

# Problem Breakdown
- **Input:** A CSV file that contains data from two sensors measuring the distance from each sensor to the basketball at various points in time for each shot taken.
- **Output:** A prediction of whether the basketball scores or misses based on each basketball’s trajectory after a shot has been taken.
- **Assumption:** Because it’s a 2D problem, I will be using x and y coordinates, with x being the horizontal plane while y represents the vertical plane.

# Reading Data
Data in the CSV file is grouped according to basketball shot numbers, where each shot has two sets of measurements for each sensor. For retrieval, I used the `ifstream` function from the `fstream` class, the `getline` function, and `stringstream` from the `sstream` library. 

To store this data, I made use of the **Map ADT**, where a pair of measurements is mapped to a basketball number so that I can easily access the data.

Before mapping, I retrieved and cast the data to perform simple arithmetic to validate my casting.

# Processing Data

## Position Calculation Algorithm (`calcPosition`)
This function determines the ball’s coordinates based on the two sensors. Its inputs are the distance from **sensor 1** to the ball and the distance from **sensor 2** to the ball. It outputs a `Ball` object that represents the calculated position of the basketball at each given time.

The algorithm follows these calculations:

\[
\text{knownDistances} = \text{dist}_1^2 - \text{dist}_2^2 - \text{SENSOR1\_X}^2 + \text{SENSOR2\_X}^2
\]

\[
\text{horizontalX} = 2 (\text{SENSOR2\_X} - \text{SENSOR1\_X})
\]

\[
x = \frac{\text{knownDistances}}{\text{horizontalX}}
\]

\[
y = \sqrt{\text{dist}_1^2 - x^2}
\]

Using the known positions of the sensors and the measured distances, I found the **x** and **y** coordinates.

## Trajectory Evaluation Algorithm (`evaluateGoal`)
This function checks whether any point in the trajectory intersects the hoop. It takes in a vector of `Ball` objects and outputs a **Boolean** indicating whether the basketball goes in or not.

The algorithm follows these calculations:

\[
\text{distance} = \sqrt{(x - \text{HOOP\_X})^2 + (y - \text{HOOP\_Y})^2}
\]

\[
\text{distance} \leq \text{HOOP\_RADIUS}
\]

If the **distance** is less than or equal to the combined radius of the ball and the hoop, the ball scores; otherwise, it misses.

# Main Workflow
1. **Load Data:** Open and read the CSV file, mapping the data to its corresponding basketball.
2. **Calculate Trajectories:** Using the `calcPosition` function for each ball, calculate the positions and store them in a vector.
3. **Evaluate Goal:** Using the `evaluateGoal` function, determine if the basketball scores. Print the trajectories and results.

This is what the program output looks like; I will submit the results in a separate text file.

# Conclusion
I believe that this solution effectively models the presented challenge using both geometric and programming principles to evaluate whether the basketball lands in the hoop. According to my solution, **basketball 4 scores**.
